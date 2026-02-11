p7_tophits_Grow(P7_TOPHITS *h)
{
  void   *p;
  P7_HIT *ori    = h->unsrt;
  int     Nalloc = h->Nalloc * 2;
  int     i;
  int     status;

  if (h->N < h->Nalloc) return eslOK;

  ESL_RALLOC(h->hit,   p, sizeof(P7_HIT *) * Nalloc);
  ESL_RALLOC(h->unsrt, p, sizeof(P7_HIT)   * Nalloc);


  if (h->is_sorted_by_seqidx || h->is_sorted_by_sortkey)
  {
      for (i = 0; i < h->N; i++)
        h->hit[i] = h->unsrt + (h->hit[i] - ori);
  }

  h->Nalloc = Nalloc;
  return eslOK;

 ERROR:
  return eslEMEM;
}
