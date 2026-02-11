utest_SequenceSubset(ESL_MSA *m1)
{
  char    *msg   = "SequenceSubset() unit test failure";
  ESL_MSA *m2    = NULL;
  int     *useme = NULL;
  int      i,j;
  int      n2;


  useme = malloc(m1->nseq * sizeof(int));
  for (i = 0, n2 = 0; i < m1->nseq; i++)
    if (i%2 == 0) { useme[i] = TRUE; n2++; }
    else          useme[i] = FALSE;

  if (esl_msa_SequenceSubset(m1, useme, &m2) != eslOK) esl_fatal(msg);
  if (m2->nseq != n2) esl_fatal(msg);

  for (i = 0, j = 0; i < m1->nseq; i++)
    {
      if (useme[i])
	{
	  if (strcmp(m1->sqname[i], m2->sqname[j]) != 0) esl_fatal(msg);
	  if (! (m1->flags & eslMSA_DIGITAL) && (strcmp(m1->aseq[i],   m2->aseq[j])  != 0)) esl_fatal(msg);
#ifdef eslAUGMENT_ALPHABET
	  if (  (m1->flags & eslMSA_DIGITAL) && memcmp(m1->ax[i], m2->ax[j], sizeof(ESL_DSQ) * (m1->alen+2)) != 0) esl_fatal(msg);
#endif
	  j++;
	}
    }
  esl_msa_Destroy(m2);
  free(useme);
  return;
}
