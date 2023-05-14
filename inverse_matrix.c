                    /**********************************************************|
                    |--------------# Student SNOUSSI ABDERRAHMAN #-------------|
                    |-----------# Inverse square matrix of size N*N #----------|
                    |**********************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//  this function return the pgcd of two number x and y
int PGCD(int x,int y)
{
    if(x == 0 && y != 0)
    return y;
    if(y == 0 && x != 0)
    return x;
    while(x != y)
    {
        if(x > y)
        x -= y;
        if(y > x)
        y -= x;
    }
    return x;
}
//  function return the signal of the number 
int signal(int number)
{
    if(number < 0)
      return -1;
    return 1;
}
// changed of two number and value int_or_float representing if int 0 or float 1
void change_two_number(int num1,int num2,int int_or_float)
{
    if(!int_or_float)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    if(int_or_float)
    {
        float temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
//   function that return the PGCD of row of index i in the matrix
int PGCD_row(int mat[10][10],int N,int index)   
{
    int pgcd=0,sig=1;
    for(int j=0; j < N ;j++)
    {
      if(mat[index][j] < 0)
      pgcd=PGCD(pgcd,-mat[index][j]);
      else pgcd=PGCD(pgcd,mat[index][j]);
      sig *= signal(mat[index][j]);   // change the signal every time
    }
    return pgcd*sig;
}
//    function to divide row in matrix by number 
void divide_by_number(int mat[10][10],float Inv[10][10],int N,int i,int numb)  
{
    for(int j=0 ; j < N ; j++)
    {
        mat[i][j]/=numb;
        Inv[i][j]/=numb;
    }
}
//   searche pivot non null 
int test_pivot(int mat[10][10],int N,int piv)   
{
    for(int i = piv ; i < N ; i++)
    {
        if(mat[i][piv] != 0)
        return 0;
    }
    return 1;
}
//   determine non-zero pivot index
int search_pivot(int mat[10][10],int N,int piv) 
{
    for(int i=piv ; i < N ; i++)
    {
        if(mat[i][piv] != 0)
        return i;
    }
}
//    inverse two lines i1 and i2 for start to i1
void inverse_row(int mat[10][10],float Inv[10][10],int N,int i1,int i2)   
{
    for(int j=i1 ; j < N ; j++)
    {
        change_two_number(mat[i1][j],mat[i2][j],0);
        change_two_number(Inv[i1][j],Inv[i2][j],1);
    }
}
//  echlone ich line by ip pivot line 
void echlone(int mat[10][10],float Inv[10][10],int N,int index_piv,int ich)  
{
    int number_piv,temp;
      number_piv = mat[index_piv][index_piv];
      temp = mat[ich][index_piv];
    for(int j=index_piv ; j < N ; j++)
      mat[ich][j] = mat[ich][j]*number_piv-mat[index_piv][j]*temp;
    for(int j=0 ; j < N ; j++)
      Inv[ich][j] = Inv[ich][j]*number_piv-Inv[index_piv][j]*temp;
}
//  Initializes the identity matrix of size N 
void  initial_identity_matrix(float Inv[10][10],int N)   
{
    for(int i=0; i < N ;i++)
    {
        for(int j=0; j < N ;j++)
        {
            if(i == j)
            Inv[i][j] = 1.0;
            else
            Inv[i][j] = 0.0;
        }
    }
}
//    function to calculate matrix determiner  
int determiner(int mat[10][10],int N)      
{
  int  det=0 , T[10][10] , p, h, k, i, j;
  if(N == 1)
  return mat[0][0];
  else if(N == 2)
  {
    det = mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
    return det;
  }
  if(N != 1 && N != 2)
    {
      for(p=0; p < N ;p++)
      {
        h = 0;
        k = 0;
        for(i=1; i < N ;i++)
        {
          for( j=0; j < N ;j++)
          {
            if(j == p)
            continue;
            T[h][k] = mat[i][j];
            k++;
             if(k == N-1)
              {
               h++;
               k = 0;
              }
          }
        }
        det+= mat[0][p]*pow(-1,p)*determiner(T,N-1);
      }
     return det;
    }
}
//   echlone all matrix for line 
void echlone_all_matrix(int mat[10][10],float inv[10][10],int N)
{
    int index_pivot,pgcd;
    for(int k=0 ; k < N-1 ; k++)
    {
       if(test_pivot(mat,N,k) == 0)
       {
          index_pivot = search_pivot(mat,N,k);
          if(index_pivot != 0)
          inverse_row(mat,inv,N,k,index_pivot);
          for(int i=k+1 ; i < N ;i++)
          {
            if(mat[i][k] != 0)
            {
                echlone(mat,inv,N,k,i);
                pgcd = PGCD_row(mat,N,i);
                divide_by_number(mat,inv,N,i,pgcd);
            }
          }
       }
    }
}
//  echlone after at the highest 
void echlone_highest(int mat[10][10],float inv[10][10],int N)
{
    int pgcd;
    for(int k=N-1 ; k > 0 ; k--)
    {
      for(int i=k-1 ; i >= 0 ;i--)
        {
           if(mat[i][k] != 0)
            {
                echlone(mat,inv,N,k,i);           
                pgcd = PGCD_row(mat,N,i);
                divide_by_number(mat,inv,N,i,pgcd);
            }
        }
    }
}
// print the matrix inverse  //
void print_matrix_inverse(float Inv[10][10],int N,int det)
{
    printf(" ************************************ \n");
    for(int i=0 ; i < N ; i++)    
    {
        for(int j=0 ; j < N ; j++)
        printf(" %.2f ",det*Inv[i][j]);
        printf("\n");
    }
    printf(" the matrix divides by the number = %d ",det);
}

/*********************************************************************/
int main()
{
    int mat[10][10];
    float Inv[10][10];
    int N,i,j,k,index_pivot,pgcd,det;
    system("cls");
    system("color 0c");
    printf("\n \t\t\t |*****************************************************************|");
    printf("\n \t\t\t |*.............. Inverse square matrix of size N*N ..............*|");
    printf("\n \t\t\t |*...................... Echlone by line ........................*|");
    printf("\n \t\t\t |*****************************************************************|");
    do{
        printf("\n Give the square matrix size N : ");
        scanf("%d",&N);
    }while(N <= 0 || N > 10 );
    printf("\n Donner la matrice : \n");
    for(i=0 ; i < N ; i++)
    {
       for(j=0 ; j < N ; j++)
       scanf("%d",&mat[i][j]);
    }
    det = determiner(mat,N);
     if(det == 0)                  /* We must determine is null then the matrix is ​​not invertible */
    {
       printf("\n the matrix not invertible because det(matrix) = 0 .");
       return 0;
    }
    initial_identity_matrix(Inv,N);
    echlone_all_matrix(mat,Inv,N);
    echlone_highest(mat,Inv,N);
    print_matrix_inverse(Inv,N,det);
    return 0;
}
