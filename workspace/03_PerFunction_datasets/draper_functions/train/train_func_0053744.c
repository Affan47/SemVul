esl_dst_CDiffMx(char **as, int N, ESL_DMATRIX **ret_D)
{
  ESL_DMATRIX *D = NULL;
  int status;
  int i,j;

  status = esl_dst_CPairIdMx(as, N, &D);
  if (status != eslOK) goto ERROR;

  for (i = 0; i < N; i++)
    {
      D->mx[i][i] = 0.;
      for (j = i+1; j < N; j++)
	{
	  D->mx[i][j] = 1. - D->mx[i][j];
	  D->mx[j][i] = D->mx[i][j];
	}
    }

  if (ret_D != NULL) *ret_D = D; else esl_dmatrix_Destroy(D);
  return eslOK;

 ERROR:
  if (D     != NULL)  esl_dmatrix_Destroy(D);
  if (ret_D != NULL) *ret_D = NULL;
  return status;

}
