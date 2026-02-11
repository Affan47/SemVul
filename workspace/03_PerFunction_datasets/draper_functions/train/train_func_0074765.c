gt_sain_endbuckets(GtSainseq *sainseq)
{
  unsigned long charidx, previous;

  previous = sainseq->bucketfillptr[0] = sainseq->bucketsize[0];
  for (charidx = 1UL; charidx < sainseq->numofchars; charidx++)
  {
    previous += sainseq->bucketsize[charidx];
    sainseq->bucketfillptr[charidx] = previous;
  }
}
