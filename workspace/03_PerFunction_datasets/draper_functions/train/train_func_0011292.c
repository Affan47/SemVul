SparseMatrix_multiply_dense(SparseMatrix A, int ATransposed, real *v, int vTransposed, real **res, int res_transposed, int dim){


  if (!vTransposed) {
    SparseMatrix_multiply_dense1(A, v, res, dim, ATransposed, res_transposed);
  } else {
    SparseMatrix_multiply_dense2(A, v, res, dim, ATransposed, res_transposed);
  }

}
