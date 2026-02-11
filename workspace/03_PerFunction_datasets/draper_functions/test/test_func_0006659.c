alloc_vjd_yshadow_deck(int L, int i, int j)
{
  int status;
  char **a;
  int    jp;
  ESL_ALLOC(a, sizeof(char *) * (L+1));
  for (jp = 0;   jp < i-1;    jp++) a[jp] = NULL;
  for (jp = j+1; jp <= L;     jp++) a[jp] = NULL;
  for (jp = 0;   jp <= j-i+1; jp++) ESL_ALLOC(a[jp+i-1], sizeof(char) * (jp+1));
  return a;
 ERROR:
  cm_Fail("Memory allocation error.");
  return NULL;
}
