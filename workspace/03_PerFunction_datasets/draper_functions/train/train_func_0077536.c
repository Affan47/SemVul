reed_sol_r6_coding_matrix(int k, int w)
{
  int *matrix;
  int i, tmp;

  if (w != 8 && w != 16 && w != 32) return NULL;

  matrix = talloc(int, 2*k);
  if (matrix == NULL) return NULL;

  for (i = 0; i < k; i++) matrix[i] = 1;
  matrix[k] = 1;
  tmp = 1;
  for (i = 1; i < k; i++) {
    tmp = galois_single_multiply(tmp, 2, w);
    matrix[k+i] = tmp;
  }
  return matrix;
}
