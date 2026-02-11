gt_seq_iterator_fastq_set_chardisttab(GtSeqIterator *si,
                                          unsigned long *chardist)
{
  GtSeqIteratorFastQ *seqit;
  gt_assert(si && chardist);
  seqit = gt_seq_iterator_fastq_cast(si);
  seqit->chardisttab = chardist;
}
