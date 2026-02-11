esl_paml_ReadE(FILE *fp, ESL_DMATRIX *E, double *pi)
{
  int             status;
  ESL_FILEPARSER *efp = NULL;
  char           *tok;
  int             i,j;
  char           *pamlorder = "ARNDCQEGHILKMFPSTWYV";
  char           *eslorder  = "ACDEFGHIKLMNPQRSTVWY";
  int             perm[20];

  if ((status =  esl_dmatrix_SetZero(E))                 != eslOK) goto ERROR;
  esl_vec_DSet(pi, 20, 0.);

  if ((efp =    esl_fileparser_Create(fp))               == NULL)  goto ERROR;
  if ((status = esl_fileparser_SetCommentChar(efp, '#')) != eslOK) goto ERROR;


   for (i = 0; i < 20; i++)
     perm[i] = (int) (strchr(eslorder, pamlorder[i]) - eslorder);


   for (i = 1; i < 20; i++)
    for (j = 0; j < i; j++)
      {
	if ((status = esl_fileparser_GetToken(efp, &tok, NULL)) != eslOK) goto ERROR;
	E->mx[perm[i]][perm[j]] = atof(tok);
	E->mx[perm[j]][perm[i]] = E->mx[perm[i]][perm[j]];
      }


  for (i = 0; i < 20; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, NULL)) != eslOK) goto ERROR;
      pi[perm[i]] = atof(tok);
    }

  esl_fileparser_Destroy(efp);
  return eslOK;

 ERROR:
  if (efp != NULL) esl_fileparser_Destroy(efp);
  return status;
}
