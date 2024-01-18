#include <stdio.h>
#include <stdlib.h>

/*PROGRAM ERRORS*/
#define ALLOCATION_ERROR                  0
#define ORDER_ERROR                       "Matrix should be square, try again.\n"
#define OPTION_ERROR                      "Invalid option, try again!\n"
#define ERROR                             "Input Error!"
#define ALLOCATION_SUCCESS                1
#define INCORRECT                         1

/*PROGRAM REQUESTS*/
#define MATRIX_TRANSPOSE                  1
#define POLYNOMIAL_MATRIX                 2
#define EXIT                              3

#define COEFFICIENTS                      3  /*THIS IS THE COEFFICIENTS NUMBER*/
#define A0                                0  /*FIRST POLYNOMIAL COEFFICIENT*/
#define A1                                1  /*SECOND POLYNOMIAL COEFFICIENT*/
#define A2                                2  /*THIRD POLYNOMIAL COEFFICIENT*/

/*PROGRAM PROMPTS*/
#define WELCOME                          "Welcome to Matrix Calculator\nEnter 1 for matrix transpose, 2 for polynomial matrix, 3 to exit:\n"
#define END                              "Thank you for using Matrix Calculator!"
#define POLYNOMIAL_RESULT                "The result matrix is:\n"
#define TRANSPOSE_RESULT                 "The transpose matrix is:\n"
#define ENTER_REQUEST                    "Enter 1 for matrix transpose, 2 for polynomial matrix, 3 to exit:\n"
#define ENTER_COEFFICIENT                "Enter %d coefficient:\n"
#define ENTET_MATRIX                     "Please enter matrix:\n"
#define ENTER_DIMENSIONS                 "Enter matrix dimensions:\n"

int i, j;  /*VAIRABLES USED IN LOOPS THROUGHOUT THE PROGRAM*/
int row, col;    /*THIS VAIRABLE IS USED TO TAKE THE ROWS&COLS NUMBER IN EACH MATRIX ENTERED*/
int** p_matrix;  /*THIS MATRIX IS ENTERED BY THE USER IN THE POLYNOMIAL PLACEMENT REQUEST*/
int** multiply_matrix;/*THIS MATRIX IS USED TO BE THE RESULT MATRIX AFTER THE MULTIPLICATION IN THE POLYNOMIAL PLACEMENT*/
int coefficient[COEFFICIENTS];

/*FUNCTIONS DEFINITIONS*/
int mat_allocation(int*** mat, int row, int col);
void free_mat(int** mat,int row);
int matrix_order();
int Read_matrix(int** matrix,int row, int col);
void Print_Transpose(int **matrix, int row,int col);
int Polynomial_coefficient(int coefficient[], int size);
void Zero_Initialization(int** matrix, int row, int col);
void matrix_multiplication(int** matrix, int** multiply_matrix, int row, int col);
void Polynomial_Matrix_Result(int** matrix, int row, int col);
void Polynomial_Matrix_Print(int** polynomial_matrix,int row, int col);
void The_End();
void Input_Error();

/**
*mat_allocation FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO ALLOCATE MEMORY FOR EACH MATRIX USED IN THIS PROGRAM.
*
*PARAMETERS :  @mat
*              @row
*              @col
*
*RETURN VALUES: REURN 1 IF ALLOCATION_SUCCESS 0 FOR ALLOCATION_ERROR.
*/
int mat_allocation(int*** mat, int row, int col)
{
    (*mat)=(int**)malloc((row*col)*sizeof(int));   /*ALLOCATING MEMORY TO EACH MATRIX USED IN THE PROGRAM*/
    if(mat==NULL)
    {
        free(mat); /*FREEING MEMORY IN CASE THE ALLOCATION FAILED*/
        return ALLOCATION_ERROR;
    }
    for(i=0; i<row; i++)
    {
        (*mat)[i] = (int*)malloc(col*sizeof(int));
        if((*mat)[i]==NULL)
        {
            free_mat(*mat,row);
            free(mat);
            return ALLOCATION_ERROR;
        }
    }
    return ALLOCATION_SUCCESS;
}

/**
*free_mat FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO FREE THE MEMORY FOR EACH MATRIX USED IN THIS PROGRAM.
*
*PARAMETERS :  @mat
*              @row
*
*RETURN VALUES: -.
*/
void free_mat(int** mat,int row)
{
    i=0;
    while(i<row ) /*FREEING MEMORY FROM THE INTERNAL ARRAYES THEN THE EXTERNAL ARRAY*/
        free(mat[i++]);
    free(mat);
    return; /*FUNCTION END*/
}

/**
*matrix_order FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO TAKE THE DIMENSIONS FOR THE MATRIX IN THE MATRIX_TRANSPOSE OPTION OR THE POLYNOMIAL_MATRIX.
*
*PARAMETERS: -.
*
*RETURN VALUES: 0 IF THE INPUT IS CORRECT , 1 IF THE INPUT IS NOT CORRECT.
*/
int matrix_order()
{
    int check=0;
    while(1)
    {
        printf(ENTER_DIMENSIONS);
        check=scanf("%d",&row); /*TAKING ROWS NUMBER FOR THE MATRIX*/
        if(check<INCORRECT) /*ROWS INPUT ISN'T CORRECT*/
        {
            return 1;
        }
        check=scanf("%d",&col); /*TAKING COLS NUMBER FOR THE MATRIX*/
        if(check<INCORRECT)
        {
            return 1;
        }
        if(row<=0||col<=0)
        {
            continue; /* ENTER DIMENSIONS AGAIN IF THE INPUT IS NEGATIVE NUMBER*/
        }
        return 0;
    }
}

/**
*Read_matrix FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO READ THE ELEMENTS FOR EACH REQUEST (TRANSPOSE / POLYNOMIAL).
*
*PARAMETERS :  @matrix
*              @row
*              @col
*
*RETURN VALUES: 0 IF THE INPUT IS CORRECT , 1 IF THE INPUT IS NOT CORRECT..
*/
int Read_matrix(int** matrix, int row, int col)
{
    int check=0; /*USED TO CHECK THE CORRECTLY OF EACH INPUT*/
    printf(ENTET_MATRIX);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            check=scanf("%d", &matrix[i][j]); /*TAKING THE ELEMENTS OF THE MATRIX*/
            if(check<INCORRECT) /*ONE ELEMENT OR MORE IN THE MATRIX IS NOT A CORRECT INPUT*/
            {
                return 1;
            }
        }
    }
    return 0;
}

/**
*Print_Transpose FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO PRINT THE TRANSPOSE MATRIX RESULT .
*
*PARAMETERS :  @matrix
*              @row
*              @col
*
*RETURN VALUES: - .
*/
void Print_Transpose(int** matrix, int row, int col)
{
    printf(TRANSPOSE_RESULT);
    /*THIS FUNCTION PRINTING THE TRANSPOSE MATRIX THE ROWS IN THE ORIGINAL MATRIX PRINTED AS A COLS AND COLS PRINTED AS A ROWS*/
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            if(row-j==1)
            {
                printf("%d",matrix[j][i]); /*PRINTING THE LAST TRANSPOSE MATRIX ELEMENTS ROW WITHOUT THIS SIGN ---> ( , ) */
            }
            else
            {
                printf("%d, ",matrix[j][i]); /*PRINTING TRANSPOSE MATRIX ELEMENTS*/
            }
        }
        printf("\n");
    }
    return;
}

/**
*Polynomial_coefficient FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO TAKE THE COEFFICIENTS.
*
*PARAMETERS :  @coefficient (array)
*              @size
*
*RETURN VALUES: 0 IF THE INPUT IS CORRECT , 1 IF THE INPUT IS NOT CORRECT..
*/
int Polynomial_coefficient(int coefficient[], int size)
{
    int check=0;
    for(i=0; i<COEFFICIENTS; i++)
    {
        printf(ENTER_COEFFICIENT,i);
        check=scanf("%d",&coefficient[i]); /*TAKING POLYNOM COEFFICIENTS FROM*/
        if(check<INCORRECT)
        {
            return 1;
        }
    }
    return 0;
}

/**
*Zero_Initialization FUNCTION.
*
*EXPLANATION: THIS FUNCTION USED TO INITIALIZE MATRIXES USED IN THE PROGRAM WITH 0.
*
*PARAMETERS :  @matrix
*              @row
*              @col
*
*RETURN VALUES: - .
*/
void Zero_Initialization(int** matrix, int row, int col)
{
    for(i=0; i<row; i++)/*MATRIX INITIALIZATION WITH 0*/
    {
        for(j=0; j<col; j++)
        {
            matrix[i][j]=0;
        }
    }
    return;
}

/**
*matrix_multiplication FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO MULTIPLICATE THE MATRIX TO HELP CALCULATE THE FINAL MATRIX WITH POLYNOMIAL PLACEMENT .
*
*PARAMETERS :  @matrix
*              @multiply_matrix : MATRIX INTILIZED WITH 0 (multiply_matrix) TO PUT THE RESULT OF THE POLYNOMIAL MATRIX MULTIPLICATION RESULT IN IT
*              @row
*              @col
*
*RETURN VALUES: - .
*/
void matrix_multiplication(int** matrix,int** multiply_matrix, int row, int col)
{
    int k;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            for (k = 0; k <col ; k++)
            {
                multiply_matrix[i][j]+=matrix[i][k] * matrix[k][j];/*CALCULATING THE RESULT MATRIX AFTER THE MULTIPLICATON*/
            }
        }
    }
    return;
}

/**
*Polynomial_Matrix_Result FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO MAKE THE FINAL POLYNOMIAL MATRIX , FIRST CREATING THE UNIT MATRIX IN THE SAME MATRIX ORDER
AND THEN CALCULATING THE FINAL POLYNOMIAL MATRIX WITH THE POLYNOMIAL PLACEMENT .
*
*PARAMETERS :  @matrix : THIS MATRIX IS INTILIZED WITH 0, TO PUT THE FINAL MATRIX AFTER THE CALCULATING IN IT
*              @row
*              @col
*
*RETURN VALUES: - .
*/
void Polynomial_Matrix_Result(int** matrix,int row,int col)
{
    j=0;
    for(i=0; i<row; i++)
    {
        matrix[i][j]=1;/*BUILDUNG THE UNIT MATRIX BASED ON THE GIVEN MATRIX ORDER(FOR THE FIRST COEFFICIENT*/
        j++;
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            /*CALCULATING THE FINAL MATRIX WITH POLYNOMIAL PLACEMENT (EACH COEFFICIENT MULTIPLIED IN HIS MATRIX ELEMENTS*/
            matrix[i][j]=(coefficient[A0]*matrix[i][j])+(coefficient[A1]*p_matrix[i][j])+(coefficient[A2]*multiply_matrix[i][j]);
        }
    }
    return;
}

/**
*Polynomial_Matrix_Print FUNCTION.
*
*EXPLANATION: THIS FUNCTION IS USED TO PRINT THE POLYNOMIAL MATRIX.
*
*PARAMETERS :  @polynomial_matrix : THIS IS THE FINAL MATRIX (POLYNOMIAL_MATRIX) AFTER THE POLYNOMIAL PLACEMENT
*              @row
*              @col
*
*RETURN VALUES: - .
*/
void Polynomial_Matrix_Print(int** polynomial_matrix,int row, int col)
{
    printf(POLYNOMIAL_RESULT);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if(row-j==1)
            {
                printf("%d",polynomial_matrix[i][j]); /*PRINTING THE POLYNOMIAL MATRIX ELEMENTS ROW WITHOUT THIS SIGN ---> ( , ) */
            }
            else
            {
                printf("%d, ",polynomial_matrix[i][j]); /*PRINTING POLYNOMIAL MATRIX ELEMENTS*/
            }
        }
        printf("\n");
    }
    return;
}

/**
*The_End FUNCTION.
*
*EXPLANATION: FUNCTION USED TO PRINT THE PROGRAM END MESSAGE.
*
*RETURN VALUES: - .
*/
void The_End()
{
    printf(END);
    return;
}

/**
*Input_Error FUNCTION.
*
*EXPLANATION: FUNCTION USED THE PROGRAM INPUT ERROR MESSAGE.
*
*RETURN VALUES: - .
*/
void Input_Error()
{
    printf(ERROR);
    return;
}

int main()
{
    int request;
    int** matrix;
    int** polynomial_matrix;
    int check_allocation=0;/*THIS VAIRABLE USED TO CHECK THE VALUE RETURNED FROM mat_allocation FUNCTION*/
    int check_request=0; /*THIS VAIRABLE USED TO CHECK THE CORRECTLY OF THE REQUEST INPUT*/
    printf(WELCOME);
    while(1)
    {
        check_request=scanf("%d",&request); /*TAKING REQUEST FUNCTION FROM USER*/
        if(check_request<INCORRECT) /*REQUEST INPUT ISN'T CORRECT*/
        {
            Input_Error();
            return 1; /*PROGRAM ENDED*/
        }
        if(request!=MATRIX_TRANSPOSE&&request!=POLYNOMIAL_MATRIX&&request!=EXIT)/*UNKNOWN REQUEST ENTERED*/
        {
            printf(OPTION_ERROR);
            continue; /*ENTER AGAIN*/
        }
        if(request==MATRIX_TRANSPOSE)
        {
            if(matrix_order()==1)/*MATRIX ORDER INPUT ISN'T CORRECT*/
            {
                Input_Error();
                return 1;
            }
            if(mat_allocation(&matrix,row,col)==0)/*IN CASE IF ALLOCATION FAILED*/
            {
                printf("ALLOCATION ERROR!");
                return 1;
            }
            if(mat_allocation(&matrix,row,col)==1)/*ALLOCATION SUCCESS*/
            {
                if(Read_matrix(matrix,row,col)==1)/*MATRIX ELEMENTS INPUT ISN'T CORRECT*/
                {
                    Input_Error();
                    return 1;
                }
                Print_Transpose(matrix,row,col);/*FUNCTION CALL*/
                free_mat(matrix,row);
                printf(ENTER_REQUEST);
                continue;/*PROCESS FINISHED ENTER NEW REQUES*/
            }
        }
        if(request==POLYNOMIAL_MATRIX)
        {
            if(Polynomial_coefficient(coefficient, COEFFICIENTS)==1)
            {
                Input_Error();
                return 1;
            }
            while(1)
            {
                if(matrix_order()==1)
                {
                    Input_Error();
                    return 1;
                }
                if(row!=col) /*MATRIX ORDER ISN'T SQUARE*/
                {
                    printf(ORDER_ERROR);
                    continue; /*ENTER ORDER AGAIN*/
                }
                check_allocation=mat_allocation(&p_matrix,row,col);/*FUNCTION CALL TO CHECK ALLOCATION ANSWER(SUCCESS/ERROR)*/
                if(check_allocation<INCORRECT)
                {
                    printf("Allocation Error!");
                    return 1;
                }
                check_allocation=mat_allocation(&polynomial_matrix,row,col);
                if(check_allocation<INCORRECT)
                {
                    printf("Allocation Error!");
                    return 1;
                }
                check_allocation=mat_allocation(&multiply_matrix,row,col);
                if(check_allocation<INCORRECT)
                {
                    printf("Allocation Error!");
                    return 1;
                }
                if(Read_matrix(p_matrix,row,col)==1)/*READING MATRIX ELEMENTS FROM USER AND CHECK THE CORRECTLY OF EACH INPUT*/
                {
                    Input_Error();
                    return 1;
                }
                /*FUNCTIONS CALL*/
                Zero_Initialization(polynomial_matrix,row,col);
                Zero_Initialization(multiply_matrix,row,col);
                matrix_multiplication(p_matrix,multiply_matrix,row,col);
                Polynomial_Matrix_Result(polynomial_matrix,row,col);
                Polynomial_Matrix_Print(polynomial_matrix,row,col);
                free_mat(polynomial_matrix,row);
                free_mat(multiply_matrix,row);
                free_mat(p_matrix,row);
                break;/*INTERNAL WHILE LOOP ENDED*/
            }
            printf(ENTER_REQUEST);
            continue; /*ENTER REQUEST AGAIN*/
        }
        if(request==EXIT) /*EXIT REQUEST*/
        {
            The_End();
            return 0; /*PROGRAM ENDED*/
        }
    }
    return 0;
}
