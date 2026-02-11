Matrix_Closure(wordptr addr, N_int rows, N_int cols)
{
    N_word i;
    N_word j;
    N_word k;
    N_word ii;
    N_word ij;
    N_word ik;
    N_word kj;
    N_word termi;
    N_word termk;

  if ((rows == cols) and (BV_BITS_(addr) == rows*cols))
  {
    for ( i = 0; i < rows; i++ )
    {
        ii = i * cols + i;
        BIT_VECTOR_SET_BIT(addr,ii)
    }
    for ( k = 0; k < rows; k++ )
    {
        termk = k * cols;
        for ( i = 0; i < rows; i++ )
        {
            termi = i * cols;
            ik = termi + k;
            for ( j = 0; j < rows; j++ )
            {
                ij = termi + j;
                kj = termk + j;
                if ( BIT_VECTOR_TST_BIT(addr,ik) &&
                     BIT_VECTOR_TST_BIT(addr,kj) )
                     BIT_VECTOR_SET_BIT(addr,ij)
            }
        }
    }
  }
}
