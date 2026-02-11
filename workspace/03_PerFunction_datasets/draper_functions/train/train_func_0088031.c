utest_MinimGaps(char *tmpfile)
{
  char         *msg = "MinimGaps() unit test failure";
  ESLX_MSAFILE *mfp = NULL;
  ESL_MSA      *msa = NULL;
#ifdef eslAUGMENT_ALPHABET
  ESL_ALPHABET *abc = NULL;
#endif

  if (eslx_msafile_Open(NULL, tmpfile, NULL, eslMSAFILE_STOCKHOLM, NULL, &mfp) != eslOK) esl_fatal(msg);
  if (eslx_msafile_Read(mfp, &msa) != eslOK)                                             esl_fatal(msg);
  eslx_msafile_Close(mfp);
  if (esl_msa_MinimGaps(msa, NULL, "-~", FALSE) != eslOK) esl_fatal(msg);
  if (msa->alen        != 45)  esl_fatal(msg);
  if (msa->aseq[0][11] != 'L') esl_fatal(msg);
  if (msa->aseq[0][18] != 'T') esl_fatal(msg);
  esl_msa_Destroy(msa);

#ifdef eslAUGMENT_ALPHABET
  if ((abc = esl_alphabet_Create(eslAMINO)) == NULL) esl_fatal(msg);
  if (eslx_msafile_Open(&abc, tmpfile, NULL, eslMSAFILE_STOCKHOLM, NULL, &mfp) != eslOK) esl_fatal(msg);
  if (eslx_msafile_Read(mfp, &msa) != eslOK) esl_fatal(msg);
  eslx_msafile_Close(mfp);
  if (esl_msa_MinimGaps(msa, NULL, NULL, FALSE) != eslOK) esl_fatal(msg);
  if (msa->alen            != 45)  esl_fatal(msg);
  if (esl_msa_Textize(msa) != eslOK) esl_fatal(msg);
  if (msa->aseq[0][11] != 'L') esl_fatal(msg);
  if (msa->aseq[0][18] != 'T') esl_fatal(msg);
  esl_msa_Destroy(msa);
  esl_alphabet_Destroy(abc);
#endif
  return;
}
