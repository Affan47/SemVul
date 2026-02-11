jerasure_invertible_matrix(int *mat, int rows, int w)
{
  int cols, i, j, k, x, rs2;
  int row_start, tmp, inverse;

  cols = rows;


  for (i = 0; i < cols; i++) {
    row_start = cols*i;


    if (mat[row_start+i] == 0) {
      for (j = i+1; j < rows && mat[cols*j+i] == 0; j++) ;
      if (j == rows) return 0;
      rs2 = j*cols;
      for (k = 0; k < cols; k++) {
        tmp = mat[row_start+k];
        mat[row_start+k] = mat[rs2+k];
        mat[rs2+k] = tmp;
      }
    }


    tmp = mat[row_start+i];
    if (tmp != 1) {
      inverse = galois_single_divide(1, tmp, w);
      for (j = 0; j < cols; j++) {
        mat[row_start+j] = galois_single_multiply(mat[row_start+j], inverse, w);
      }
    }


    k = row_start+i;
    for (j = i+1; j != cols; j++) {
      k += cols;
      if (mat[k] != 0) {
        if (mat[k] == 1) {
          rs2 = cols*j;
          for (x = 0; x < cols; x++) {
            mat[rs2+x] ^= mat[row_start+x];
          }
        } else {
          tmp = mat[k];
          rs2 = cols*j;
          for (x = 0; x < cols; x++) {
            mat[rs2+x] ^= galois_single_multiply(tmp, mat[row_start+x], w);
          }
        }
      }
    }
  }
  return 1;
}
