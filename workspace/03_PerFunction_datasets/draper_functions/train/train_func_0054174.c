amdmsDestroyLinearFit(amdmsFIT_LINEAR_ENV **env)
{
  amdmsFIT_LINEAR_ENV   *henv = NULL;
  amdmsFIT_ENV          *hhenv = NULL;

  if (env == NULL) {
    return amdmsFAILURE;
  }
  if (*env == NULL) {
    return amdmsSUCCESS;
  }
  henv = *env;
  if (henv->matU != NULL) {
    free(henv->matU[0]);
    free(henv->matU);
    henv->matU = NULL;
  }
  if (henv->matV != NULL) {
    free(henv->matV[0]);
    free(henv->matV);
    henv->matV = NULL;
  }
  if (henv->matCvm != NULL) {
    free(henv->matCvm[0]);
    free(henv->matCvm);
    henv->matCvm = NULL;
  }
  if (henv->vecW != NULL) {
    free(henv->vecW);
    henv->vecW = NULL;
  }
  if (henv->vecB != NULL) {
    free(henv->vecB);
    henv->vecB = NULL;
  }
  hhenv = &(henv->env);
  if (amdmsDestroyFit(&hhenv) != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  if (henv->allocated) {
    henv->allocated = 0;
    free(henv);
    *env = NULL;
  }
  return amdmsSUCCESS;
}
