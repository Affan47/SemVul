esl_vec_DCompare(const double *vec1, const double *vec2, int n, double tol)
{
  int i;
  for (i = 0; i < n; i++) if (esl_DCompare(vec1[i], vec2[i], tol) == eslFAIL) return eslFAIL;
  return eslOK;
}
