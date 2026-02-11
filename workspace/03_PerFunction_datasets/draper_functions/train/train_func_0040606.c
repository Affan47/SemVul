free_vji_matrix(float ***a, int M, int j1, int j0)
{
  int v;


  for (v = 0; v <= M; v++)
    if (a[v] != NULL) { free_vji_deck(a[v], j1, j0); a[v] = NULL; }
  free(a);
}
