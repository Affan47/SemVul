sse_free_vjd_shadow_matrix(void ***shadow, CM_t *cm, int i, int j)
{
fprintf(stderr,"WARNING! sse_free_vjd_shadow_matrix has not been converted to SSE!\n");
  int v;
  for (v = 0; v < cm->M; v++)
    if (shadow[v] != NULL) {
      if (cm->sttype[v] == B_st) free_vjd_kshadow_deck((int **)  shadow[v], i, j);
      else                       free_vjd_yshadow_deck((char **) shadow[v], i, j);
      shadow[v] = NULL;
    }
  free(shadow);
}
