sse_alloc_vjd_kshadow_deck(int L, int i, int j)
{
fprintf(stderr,"WARNING! sse_alloc_vjd_kshadow_deck has not been converted to SSE!\n");
  int status;
  int **a;
  int   jp;
  ESL_ALLOC(a, sizeof(int *) * (L+1));
  for (jp = 0;   jp <  i-1;   jp++) a[jp] = NULL;
  for (jp = 0;   jp <= j-i+1; jp++) ESL_ALLOC(a[jp+i-1], sizeof(int) * (jp+1));
  for (jp = j+1; jp <= L;     jp++) a[jp] = NULL;
  return a;
 ERROR:
  cm_Fail("Memory allocation error.");
  return NULL;
}
