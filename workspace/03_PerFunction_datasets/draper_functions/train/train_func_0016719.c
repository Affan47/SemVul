p7_tophits_Create(void)
{
  P7_TOPHITS *h = NULL;
  int         default_nalloc = 256;
  int         status;

  ESL_ALLOC(h, sizeof(P7_TOPHITS));
  h->hit    = NULL;
  h->unsrt  = NULL;

  ESL_ALLOC(h->hit,   sizeof(P7_HIT *) * default_nalloc);
  ESL_ALLOC(h->unsrt, sizeof(P7_HIT)   * default_nalloc);
  h->Nalloc    = default_nalloc;
  h->N         = 0;
  h->nreported = 0;
  h->nincluded = 0;
  h->is_sorted_by_sortkey = TRUE;
  h->is_sorted_by_seqidx  = FALSE;
  h->hit[0]    = h->unsrt;
  return h;

 ERROR:
  p7_tophits_Destroy(h);
  return NULL;
}
