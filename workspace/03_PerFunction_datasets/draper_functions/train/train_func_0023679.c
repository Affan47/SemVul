cauchy_original_coding_matrix(int k, int m, int w)
{
  int *matrix;
  int i, j, index;

  if (w < 31 && (k+m) > (1 << w)) return NULL;
  matrix = talloc(int, k*m);
  if (matrix == NULL) return NULL;
  index = 0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < k; j++) {
      matrix[index] = galois_single_divide(1, (i ^ (m+j)), w);
      index++;
    }
  }
  return matrix;
}
