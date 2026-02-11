p7_bg_Create(const ESL_ALPHABET *abc)
{
  P7_BG *bg = NULL;
  int    status;

  ESL_ALLOC(bg, sizeof(P7_BG));
  bg->f     = NULL;
  bg->fhmm  = NULL;

  ESL_ALLOC(bg->f,     sizeof(float) * abc->K);
  if ((bg->fhmm = esl_hmm_Create(abc, 2)) == NULL) goto ERROR;

  if       (abc->type == eslAMINO)
    {
      if (p7_AminoFrequencies(bg->f) != eslOK) goto ERROR;
    }
  else
    esl_vec_FSet(bg->f, abc->K, 1. / (float) abc->K);

  bg->p1    = 350./351.;
  bg->omega = 1./256.;
  bg->abc   = abc;
  return bg;

 ERROR:
  p7_bg_Destroy(bg);
  return NULL;
}
