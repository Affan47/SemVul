gth_seq_con_create(const GthSeqConClass *scc)
{
  GthSeqCon *sc;
  gt_assert(scc && scc->size);
  sc = gt_calloc(1, scc->size);
  sc->c_class = scc;
  sc->pvt = NULL;
  return sc;
}
