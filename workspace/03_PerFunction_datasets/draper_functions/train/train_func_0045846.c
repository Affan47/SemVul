esl_abc_FAvgScVec(const ESL_ALPHABET *a, float *sc)
{
  ESL_DSQ x;
  for (x = a->K+1; x <= a->Kp-3; x++)
    sc[x] = esl_abc_FAvgScore(a, x, sc);
  return eslOK;
}
