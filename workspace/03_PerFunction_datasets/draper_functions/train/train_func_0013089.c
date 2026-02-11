sse_free_vji_shadow_matrix(char ***a, int M, int j1, int j0)
{
fprintf(stderr,"WARNING! sse_free_vji_shadow_matrix has not been converted to SSE!\n");
  int v;
  for (v = 0; v < M; v++)
    if (a[v] != NULL) { free_vji_shadow_deck(a[v], j1, j0); a[v] = NULL; }
  free(a);
}
