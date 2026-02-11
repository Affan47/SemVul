setup_matrix (int size) {
  int c;
  matrix_t *mat;
  int status;

  ESL_ALLOC(mat, sizeof(matrix_t));
  mat->edge_size = size;
  mat->full_size = matrix_index((size-1),(size-1)) + 1;
  mat->E = 0.0;
  mat->H = 0.0;
  ESL_ALLOC(mat->matrix, sizeof(double) * mat->full_size);
  for (c=0; c<mat->full_size; c++) {
    mat->matrix[c] = 0.0;
  }
  return(mat);

 ERROR:
  cm_Fail("Memory allocation error.");
  return NULL;
}
