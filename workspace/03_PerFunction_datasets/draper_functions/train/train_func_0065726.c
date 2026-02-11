utest_SetDegeneracy(void)
{
  char msg[]  = "esl_alphabet_SetDegeneracy() unit test failed";
  ESL_ALPHABET *a;
  char         *testseq = "yrn";
  ESL_DSQ       expect[] = { eslDSQ_SENTINEL, 6, 5, 7, eslDSQ_SENTINEL };
  ESL_DSQ      *dsq;
  ESL_DSQ       x;

  if ((a = esl_alphabet_CreateCustom("ACGT-RYN*~", 4, 10)) == NULL) esl_fatal(msg);
  if (esl_alphabet_SetDegeneracy(a, 'R', "AG") != eslOK)            esl_fatal(msg);
  if (esl_alphabet_SetDegeneracy(a, 'Y', "CT") != eslOK)            esl_fatal(msg);
  if (esl_alphabet_SetCaseInsensitive(a)       != eslOK)            esl_fatal(msg);

  if (esl_abc_CreateDsq(a, testseq, &dsq) != eslOK)                    esl_fatal(msg);
  if (memcmp(dsq, expect, sizeof(ESL_DSQ) * (strlen(testseq)+2)) != 0) esl_fatal(msg);

  x = esl_abc_DigitizeSymbol(a, 'a');  if (a->ndegen[x] != 1) esl_fatal(msg);
  x = esl_abc_DigitizeSymbol(a, 'r');  if (a->ndegen[x] != 2) esl_fatal(msg);
  x = esl_abc_DigitizeSymbol(a, 'y');  if (a->ndegen[x] != 2) esl_fatal(msg);
  x = esl_abc_DigitizeSymbol(a, 'n');  if (a->ndegen[x] != 4) esl_fatal(msg);

  free(dsq);
  esl_alphabet_Destroy(a);

#ifdef TEST_THROWING
  if ((a = esl_alphabet_CreateCustom("ACGT-RYN*~", 4, 10)) == NULL) esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, 'z', "AC")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, 'N', "ACGT")  != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, 'A', "GT")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, '-', "GT")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, '*', "GT")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, '~', "GT")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, 'R', "XY")    != eslEINVAL)          esl_fatal(msg);
  if (esl_abc_SetDegeneracy(a, 'R', "YN")    != eslEINVAL)          esl_fatal(msg);
  esl_alphabet_Destroy(a);
#endif
  return eslOK;
}
