yualtschul_func(double lambda, void *params, double *ret_fx)
{
  int status;
  struct yualtschul_params *p = (struct yualtschul_params *) params;
  ESL_DMATRIX  *S = p->S;
  ESL_DMATRIX  *M = p->M;
  ESL_DMATRIX  *Y = p->Y;
  int i,j;


  for (i = 0; i < S->n; i++)
    for (j = 0; j < S->n; j++)
      M->mx[i][j] = exp(lambda * S->mx[i][j]);


  if ((status = esl_dmx_Invert(M, Y)) != eslOK) return status;


  *ret_fx = esl_dmx_Sum(Y) - 1.;
  return eslOK;
}
