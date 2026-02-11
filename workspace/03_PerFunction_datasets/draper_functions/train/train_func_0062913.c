a2m_padding_digital(ESL_MSA *msa, char **csflag, int *nins, int ncons)
{
  ESL_DSQ *ax     = NULL;
  ESL_DSQ  gapsym = esl_abc_XGetGap(msa->abc);
  int      apos, cpos, spos;
  int      alen;
  int      icount;
  int      idx;
  int      status;

  alen = ncons;
  for (cpos = 0; cpos <= ncons; cpos++)
    alen += nins[cpos];

  ESL_ALLOC(msa->rf, sizeof(char) * (alen+1));
  for (apos = 0, cpos = 0; cpos <= ncons; cpos++)
    {
      for (icount = 0; icount < nins[cpos]; icount++) msa->rf[apos++] = '.';
      if  (cpos < ncons) msa->rf[apos++] = 'x';
    }
  msa->rf[apos] = '\0';

  for (idx = 0; idx < msa->nseq; idx++)
    {
      ESL_ALLOC(ax, sizeof(ESL_DSQ) * (alen + 2));
      ax[0] = eslDSQ_SENTINEL;
      apos = spos  = 0;
      for (cpos = 0; cpos <= ncons; cpos++)
	{
	  icount = 0;
	  while (csflag[idx][spos] == FALSE)  { ax[apos+1] = msa->ax[idx][spos+1]; apos++; spos++; icount++; }
	  while (icount < nins[cpos]) 	      { ax[apos+1] = gapsym;               apos++;         icount++; }
	  if (cpos < ncons)                   { ax[apos+1] = msa->ax[idx][spos+1]; apos++; spos++;           }
	}
      ESL_DASSERT1( (msa->ax[idx][spos+1] == eslDSQ_SENTINEL) );
      ESL_DASSERT1( (apos == alen) );
      ax[alen+1] = eslDSQ_SENTINEL;
      free(msa->ax[idx]);
      msa->ax[idx] = ax;
      ax = NULL;
    }
  msa->alen = alen;


  return eslOK;

 ERROR:
  if (ax) free(ax);
  return status;
}
