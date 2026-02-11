Matrix_Product(wordptr X, N_int rowsX, N_int colsX,
                    wordptr Y, N_int rowsY, N_int colsY,
                    wordptr Z, N_int rowsZ, N_int colsZ)
{
    N_word i;
    N_word j;
    N_word k;
    N_word indxX;
    N_word indxY;
    N_word indxZ;
    N_word termX;
    N_word termY;
    N_word sum;

  if ((colsY == rowsZ) and (rowsX == rowsY) and (colsX == colsZ) and
      (BV_BITS_(X) == rowsX*colsX) and
      (BV_BITS_(Y) == rowsY*colsY) and
      (BV_BITS_(Z) == rowsZ*colsZ))
  {
    for ( i = 0; i < rowsY; i++ )
    {
        termX = i * colsX;
        termY = i * colsY;
        for ( j = 0; j < colsZ; j++ )
        {
            indxX = termX + j;
            sum = 0;
            for ( k = 0; k < colsY; k++ )
            {
                indxY = termY + k;
                indxZ = k * colsZ + j;
                if ( BIT_VECTOR_TST_BIT(Y,indxY) &&
                     BIT_VECTOR_TST_BIT(Z,indxZ) ) sum |= 1;
            }
            if (sum) BIT_VECTOR_SET_BIT(X,indxX)
            else     BIT_VECTOR_CLR_BIT(X,indxX)
        }
    }
  }
}
