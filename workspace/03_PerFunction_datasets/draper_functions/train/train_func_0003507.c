containsspecialViatables(const GtEncseq *encseq,
                                     GtReadmode readmode,
                                     GtEncseqReader *esr,
                                     unsigned long startpos,
                                     unsigned long len)
{
  bool cspecial = false;

  gt_encseq_reader_reinit_with_readmode(esr,encseq,readmode,startpos);
  if (encseq->has_wildcardranges)
  {
    cspecial = containsSWViatables(encseq, esr, startpos, len,
                                   SWtable_wildcardrange);
  }
  if (!cspecial && encseq->numofdbsequences > 1UL)
  {
    cspecial = containsSWViatables(encseq, esr, startpos, len,
                                   SWtable_ssptab);
  }
  return cspecial;
}
