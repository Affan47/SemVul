DefaultNullModel(const ESL_ALPHABET *abc, float **ret_null)
{

  if(abc      == NULL) cm_Fail("ERROR in CMCreateNullModel, cm->abc is NULL.\n");

  int status;
  float *null = NULL;
  ESL_ALLOC(null, sizeof(float) * abc->K);
  int x;
  for (x = 0; x < abc->K; x++)
    null[x] = 1./(float) abc->K;
  esl_vec_FNorm(null, abc->K);
  *ret_null = null;
  return eslOK;

 ERROR:
  if(null != NULL) free(null);
  return status;
}
