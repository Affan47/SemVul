gt_seq_iterator_create(const GtSeqIteratorClass *sic)
{
  GtSeqIterator *si;
  gt_assert(sic && sic->size);
  si = gt_calloc((size_t) 1, sic->size);
  si->c_class = sic;
  return si;
}
