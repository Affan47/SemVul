SparseMatrix_set_entries_to_real_one(SparseMatrix A){
  real *a;
  int i;

  if (A->a) FREE(A->a);
  A->a = MALLOC(sizeof(real)*((size_t)A->nz));
  a = (real*) (A->a);
  for (i = 0; i < A->nz; i++) a[i] = 1.;
  A->type = MATRIX_TYPE_REAL;
  A->size = sizeof(real);
  return A;

}
