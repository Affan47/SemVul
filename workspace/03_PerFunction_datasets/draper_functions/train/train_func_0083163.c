utest_composition(ESL_GETOPTS *go, ESL_RANDOMNESS *r, ESL_ALPHABET *abc)
{
  char           *msg  = "p7_hmm.c:: composition unit test failed";
  P7_HMM         *hmm  = NULL;
  ESL_SQ         *sq   = esl_sq_CreateDigital(abc);
  int             M    = 3;
  int             N    = 100000;
  float          *fq   = malloc(sizeof(float) * abc->K);
  int             i,pos;

  if (p7_hmm_Sample(r, M, abc, &hmm) != eslOK)  esl_fatal(msg);
  if (p7_hmm_SetComposition(hmm)     != eslOK)  esl_fatal(msg);

  esl_vec_FSet(fq, abc->K, 0.0);
  for (i = 0; i < N; i++)
    {
      p7_CoreEmit(r, hmm, sq, NULL);

      for (pos = 1; pos <= sq->n; pos++)
	fq[sq->dsq[pos]] += 1.0;

      esl_sq_Reuse(sq);
    }
  esl_vec_FNorm(fq, abc->K);

  if (esl_opt_GetBoolean(go, "-v") == TRUE)
    {
      printf("composition unit test:\n");
      printf("  %6s %6s\n", "calced", "sample");
      printf("  %6s %6s\n", "------", "------");
      for (i = 0; i < abc->K; i++)
	printf("%c %6.3f %6.3f\n", abc->sym[i], hmm->compo[i], fq[i]);
      printf("\n");
    }

  if (esl_vec_FCompare(fq, hmm->compo, abc->K, 0.03) != eslOK) esl_fatal(msg);

  free(fq);
  esl_sq_Destroy(sq);
  p7_hmm_Destroy(hmm);
  return;
}
