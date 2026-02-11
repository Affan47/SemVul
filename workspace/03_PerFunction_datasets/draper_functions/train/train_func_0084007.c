utest_basic(void)
{
  char         *failmsg      = "failure in build.c::utest_basic() unit test";
  char          msafile[16]  = "p7tmpXXXXXX";
  FILE         *ofp          = NULL;
  ESL_ALPHABET *abc          = esl_alphabet_Create(eslAMINO);
  ESLX_MSAFILE *afp          = NULL;
  ESL_MSA      *msa          = NULL;
  P7_HMM       *hmm          = NULL;
  float         symfrac      = 0.5;

  if (esl_tmpfile_named(msafile, &ofp) != eslOK) esl_fatal(failmsg);
  fprintf(ofp, "# STOCKHOLM 1.0\n");
  fprintf(ofp, "#=GC RF --xxxxxxxxxxxxxxxx-xxx-x--\n");
  fprintf(ofp, "seq1    --ACDEFGHIKLMNPZXS-TVW-Yyy\n");
  fprintf(ofp, "seq2    aaACDEFGHIKLMNPQRS-TVWw---\n");
  fprintf(ofp, "seq3    aaAC-EFGHIKLMNPQRS-TVW-Y--\n");
  fprintf(ofp, "seq4    aaAC-EFGHIKLMNPQRS-TVW-Y--\n");
  fprintf(ofp, "//\n");
  fclose(ofp);

  if (eslx_msafile_Open(&abc, msafile, NULL, eslMSAFILE_UNKNOWN, NULL, &afp) != eslOK) esl_fatal(failmsg);
  if (eslx_msafile_Read(afp, &msa)                                           != eslOK) esl_fatal(failmsg);
  if (p7_Fastmodelmaker(msa, symfrac, NULL, &hmm, NULL)                      != eslOK) esl_fatal(failmsg);

  p7_hmm_Destroy(hmm);
  esl_msa_Destroy(msa);
  eslx_msafile_Close(afp);
  esl_alphabet_Destroy(abc);
  remove(msafile);
  return;
}
