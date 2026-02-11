esl_vec_DLogValidate(double *vec, int n, double tol, char *errbuf)
{
  int     status;
  double *expvec = NULL;

  if (errbuf) *errbuf = 0;
  if (n == 0) return eslOK;

  ESL_ALLOC(expvec, sizeof(double)*n);
  esl_vec_DCopy(vec, n, expvec);
  esl_vec_DExp(expvec, n);
  if ((status = esl_vec_DValidate(expvec, n, tol, errbuf)) != eslOK) goto ERROR;
  free(expvec);
  return eslOK;

 ERROR:
  if (expvec != NULL) free(expvec);
  return status;
}
