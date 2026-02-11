gt_SRLSaveToStream(struct seqRangeList *rangeList, FILE *fp)
{
  size_t numRanges;
  gt_assert(rangeList && fp);
  numRanges = rangeList->numRanges;
  gt_xfwrite(&(rangeList->numRanges), sizeof (rangeList->numRanges), 1, fp);
  gt_xfwrite(rangeList->ranges, sizeof (struct seqRange), numRanges, fp);
  return 1;
}
