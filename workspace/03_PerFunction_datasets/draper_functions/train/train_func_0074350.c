opr_subs(A, B)
     MATRIX *A, *B;
{
  MATRIX *C;

  double value;

  int i;

  int nrowa = NROW(A), ncola = NCOL(A);
  int nrowb = NROW(B), ncolb = NCOL(B);

  double *a = MATR(A), *b = MATR(B), *c;

  if (nrowa == nrowb && ncola == ncolb)
  {
    C = mat_new(TYPE(A),nrowa,ncola); c = MATR(C);
    nrowa *= ncola;
    for(i = 0; i < nrowa; i++) *c++ = *a++ - *b++;
  }
  else if (nrowa == 1 && ncola == 1)
  {
    C = mat_new(TYPE(B),nrowb, ncolb); c = MATR(C);
    value = *a; nrowb *= ncolb;
    for(i = 0; i < nrowb; i++) *c++ = value - *b++;
  }
  else if (nrowb == 1 && ncolb == 1)
  {
    C = mat_new(TYPE(A),nrowa,ncola); c = MATR(C);
    value = *b; nrowa *= ncola;
    for(i = 0; i < nrowa; i++) *c++ = *a++ - value;
  }
  else
    error("Substr: Incompatible for addition.\n");

  return C;
}
