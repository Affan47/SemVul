esl_wuss_full(char *oldss, char *newss)
{
  char *tmp = NULL;
  int  *ct  = NULL;
  int   n;
  int   i;
  int   status;


  n = strlen(oldss);
  ESL_ALLOC(ct,  sizeof(int)  * (n+1));
  ESL_ALLOC(tmp, sizeof(char) * (n+1));

  esl_wuss_nopseudo(oldss, tmp);

  status = esl_wuss2ct(tmp, n, ct);
  if (status != eslOK) goto ERROR;

  status = esl_ct2wuss(ct, n, tmp);
  if (status == eslEINVAL) { status = eslEINCONCEIVABLE; goto ERROR; }
  else if (status != eslOK) goto ERROR;

  for (i = 0; i < n; i++)
    if (isalpha(oldss[i])) newss[i] = oldss[i];
    else newss[i] = tmp[i];

  free(ct);
  free(tmp);
  return eslOK;

 ERROR:
  free(ct);
  free(tmp);
  return status;
}
