BWTSASSAccessOrigSeq(const void *state,
                     Symbol *dest,
                     unsigned long pos,
                     size_t len)
{
  const BWTSeqContextRetriever *ctxMap = state;
  gt_assert(state);
  gt_BWTSeqCRAccessSubseq(ctxMap, pos, len, dest);
  return len;
}
