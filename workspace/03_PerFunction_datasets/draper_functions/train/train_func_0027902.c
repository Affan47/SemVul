alloc_vji_deck(int i0, int i1, int j1, int j0)
{
  int status;
  float **a;
  int     jp;
  ESL_DPRINTF3(("alloc_vji_deck : %.4f\n", size_vji_deck(i0,i1,j1,j0)));
  ESL_ALLOC(a, sizeof(float *) * (j0-j1+1));
  for (jp = 0; jp <= j0-j1; jp++)
    ESL_ALLOC(a[jp], sizeof(float)*(i1-i0+1));
  return a;
 ERROR:
  cm_Fail("Memory allocation error.");
  return NULL;
}
