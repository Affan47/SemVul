lambda_matrix_vector_mult (lambda_matrix matrix, int m, int n,
			   lambda_vector vec, lambda_vector dest)
{
  int i, j;

  lambda_vector_clear (dest, m);
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      dest[i] += matrix[i][j] * vec[j];
}
