esl_dirichlet_DSampleUniform(ESL_RANDOMNESS *r, int K, double *p)
{
  int x;
  for (x = 0; x < K; x++)
    p[x] = esl_rnd_Gamma(r, 1.0);
  esl_vec_DNorm(p, K);
  return eslOK;
}
