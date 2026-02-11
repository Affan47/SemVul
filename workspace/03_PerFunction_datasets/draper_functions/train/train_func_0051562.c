utest_BLOSUM(ESL_ALPHABET *abc, ESL_MSA *msa, double maxid, double *expect)
{
  char *msg = "BLOSUM weights unit test failure";

  if (esl_msaweight_BLOSUM(msa, maxid)                     != eslOK) esl_fatal(msg);
  if (esl_vec_DCompare(msa->wgt, expect, msa->nseq, 0.001) != eslOK) esl_fatal(msg);

  if (abc != NULL)
    {
      if (esl_msa_Digitize(abc, msa, NULL)                     != eslOK) esl_fatal(msg);
      if (esl_msaweight_BLOSUM(msa, maxid)                     != eslOK) esl_fatal(msg);
      if (esl_vec_DCompare(msa->wgt, expect, msa->nseq, 0.001) != eslOK) esl_fatal(msg);
      if (esl_msa_Textize(msa)                                 != eslOK) esl_fatal(msg);
    }
  return eslOK;
}
