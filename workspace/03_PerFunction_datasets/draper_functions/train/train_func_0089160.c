free_vji_deck(float **a, int j1, int j0)
{
  int jp;
  ESL_DPRINTF3(("free_vji_deck called\n"));
  for (jp = 0; jp <= j0-j1; jp++)
    if (a[jp] != NULL) free(a[jp]);
  free(a);
}
