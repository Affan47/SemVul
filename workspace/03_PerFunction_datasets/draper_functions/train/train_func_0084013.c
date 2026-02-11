ccm_bg_CreateUniform(CM_CONSENSUS *ccm)
{
  CCM_BG *bg = NULL;
  int status;

  ESL_ALLOC(bg, sizeof(CCM_BG));
  bg->f = NULL;
  bg->fhmm = NULL;

  ESL_ALLOC(bg->f, sizeof(float) * ccm->abc->K);
  if ((bg->fhmm = esl_hmm_Create(ccm->abc, 2)) == NULL) goto ERROR;

  esl_vec_FSet(bg->f, ccm->abc->K, 1. / (float) ccm->abc->K);

  return bg;

 ERROR:
  ccm_bg_Destroy(bg);
  return NULL;
}
