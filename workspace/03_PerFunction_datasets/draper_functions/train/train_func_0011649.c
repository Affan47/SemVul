esl_hmx_GrowTo(ESL_HMX *mx, int L, int M)
{
  uint64_t ncells;
  void    *p;
  int      do_reset = FALSE;
  int      i;
  int      status;

  if (L < mx->allocR && M <= mx->allocM) return eslOK;


  ncells = (L+1) * M;
  if (ncells > mx->ncells)
    {
      ESL_RALLOC(mx->dp_mem, p, sizeof(float) * ncells);
      mx->ncells = ncells;
      do_reset   = TRUE;
    }


  if (L >= mx->allocR)
    {
      ESL_RALLOC(mx->dp, p, sizeof(float *) * (L+1));
      ESL_RALLOC(mx->sc, p, sizeof(float)   * (L+2));
      mx->allocR = L+1;
      mx->allocM = M;
      do_reset   = TRUE;
    }


  if (M > mx->allocM)
    {
      mx->allocM = M;
      do_reset = TRUE;
    }


  if (L >= mx->validR)
    do_reset = TRUE;


  if (do_reset)
    {
      mx->validR = ESL_MIN(mx->ncells / mx->allocM, mx->allocR);
      for (i = 0; i < mx->validR; i++)
	mx->dp[i] = mx->dp_mem + i*mx->allocM;
    }
  mx->M = 0;
  mx->L = 0;
  return eslOK;

 ERROR:
  return status;
}
