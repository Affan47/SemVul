utest_WriteNewick(ESL_RANDOMNESS *r, int ntaxa)
{
  char     *msg      = "esl_tree_WriteNewick unit test failed";
  char   tmpfile[32] = "esltmpXXXXXX";
  FILE     *fp       = NULL;
  ESL_TREE *T1       = NULL;
  ESL_TREE *T2       = NULL;
  char  errbuf[eslERRBUFSIZE];

  if (esl_tmpfile(tmpfile, &fp)            != eslOK) esl_fatal(msg);
  if (esl_tree_Simulate(r, ntaxa, &T1)     != eslOK) esl_fatal(msg);
  if (esl_tree_SetTaxonlabels(T1, NULL)    != eslOK) esl_fatal(msg);
  if (esl_tree_Validate(T1, NULL)          != eslOK) esl_fatal(msg);
  if (esl_tree_WriteNewick(fp, T1)         != eslOK) esl_fatal(msg);
  rewind(fp);
  if (esl_tree_ReadNewick(fp, errbuf, &T2) != eslOK) esl_fatal(msg);
  if (esl_tree_Validate(T2, NULL)          != eslOK) esl_fatal(msg);
  if (esl_tree_Compare(T1, T2)             != eslOK) esl_fatal(msg);
  fclose(fp);

  esl_tree_Destroy(T1);
  esl_tree_Destroy(T2);
  return;
}
