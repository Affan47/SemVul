cm_tophits_GetMaxAccessionLength(CM_TOPHITS *h)
{
  int i, max, n;
  for (max = 0, i = 0; i < h->N; i++)
    if (h->unsrt[i].acc != NULL) {
      n   = strlen(h->unsrt[i].acc);
      max = ESL_MAX(n, max);
    }
  return max;
}
