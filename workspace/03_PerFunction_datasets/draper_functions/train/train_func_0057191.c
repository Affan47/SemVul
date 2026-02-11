SparseMatrix_general_new(int m, int n, int nz, int type, size_t sz, int format){


  SparseMatrix A;

  A = SparseMatrix_init(m, n, type, sz, format);

  if (nz > 0) A = SparseMatrix_alloc(A, nz);
  return A;

}
