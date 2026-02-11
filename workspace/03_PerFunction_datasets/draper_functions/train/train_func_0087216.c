add_square_matrices(int n, const ergo_real* A, const ergo_real* B, ergo_real* C)
{
  int n2 = n*n;
  for(int i = 0; i < n2; i++)
    C[i] = A[i] + B[i];
  return 0;
}
