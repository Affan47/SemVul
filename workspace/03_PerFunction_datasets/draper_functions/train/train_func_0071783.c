esl_vec_FCompare(const float *vec1, const float *vec2, int n, float tol)
{
  int i;
  for (i = 0; i < n; i++) if (esl_DCompare(vec1[i], vec2[i], tol) == eslFAIL) return eslFAIL;
  return eslOK;
}
