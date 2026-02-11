opr_mul(A, B)
     MATRIX *A, *B;
{
  MATRIX *C;

  double value,s;
  int i, j, k;

  int nrowa = NROW(A), ncola = NCOL(A);
  int nrowb = NROW(B), ncolb = NCOL(B);

  double *a = MATR(A), *b = MATR(B), *c;

  if (nrowa == 1 && ncola == 1)
  {
    C = mat_new(TYPE(B), nrowb, ncolb); c = MATR(C);
    value = *a; nrowb *= ncolb;
    for(i = 0; i < nrowb; i++) *c++ = value * *b++;
  }
  else if (nrowb == 1 && ncolb == 1)
  {
    C = mat_new(TYPE(A), nrowa, ncola); c = MATR(C);
    value = *b; nrowa *= ncola;
    for(i = 0; i < nrowa; i++) *c++ = value * *a++;
  }
  else if (ncola == nrowb)
  {
    C = mat_new(TYPE(A), nrowa,ncolb);
    c = MATR(C);
    for(i = 0; i < nrowa; i++)
    {
      for(j = 0; j < ncolb; j++)
      {
        s = 0;
	for(k = 0; k < ncola; k++) s += a[k] * MB(k,j);
	*c++ = s;
      }
      a += ncola;
    }
  }
  else if ( ncola == ncolb && nrowa == nrowb )
  {
    C = mat_new(TYPE(A), nrowa,ncolb);
    c = MATR(C);
    k = 0;
    for( i = 0; i < nrowa; i++ )
        for( j = 0; j < ncolb; j++,k++ ) c[k] = a[k] * b[k];
  }
  else
  {
     error("Mul: Incompatible for multiplication.\n");
  }

  return C;
}
