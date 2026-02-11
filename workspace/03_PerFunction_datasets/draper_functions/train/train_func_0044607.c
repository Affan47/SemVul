utest_Invert(ESL_DMATRIX *A)
{
  char *msg = "Failure in matrix inversion unit test";
  ESL_DMATRIX *Ai = NULL;
  ESL_DMATRIX *B  = NULL;
  ESL_DMATRIX *I  = NULL;

  if ((Ai = esl_dmatrix_Create(A->n, A->m)) == NULL)  esl_fatal(msg);
  if ((B  = esl_dmatrix_Create(A->n, A->m)) == NULL)  esl_fatal(msg);
  if ((I  = esl_dmatrix_Create(A->n, A->m)) == NULL)  esl_fatal(msg);
  if (esl_dmx_Invert(A, Ai)                 != eslOK) esl_fatal("matrix inversion failed");
  if (esl_dmx_Multiply(A,Ai,B)              != eslOK) esl_fatal(msg);
  if (esl_dmatrix_SetIdentity(I)            != eslOK) esl_fatal(msg);
  if (esl_dmatrix_Compare(B,I, 1e-12)       != eslOK) esl_fatal("inverted matrix isn't right");

  esl_dmatrix_Destroy(Ai);
  esl_dmatrix_Destroy(B);
  esl_dmatrix_Destroy(I);
  return;
}
