p7_tophits_GetMaxPositionLength(P7_TOPHITS *h)
{
  int i, max, n;
  char buffer [11];

  for (max = 0, i = 0; i < h->N; i++) {
    if (h->unsrt[i].dcl[0].iali > 0) {
      n = sprintf (buffer, "%d", h->unsrt[i].dcl[0].iali);
      max = ESL_MAX(n, max);
      n = sprintf (buffer, "%d", h->unsrt[i].dcl[0].jali);
      max = ESL_MAX(n, max);
    }
  }
  return max;
}
