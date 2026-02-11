gt_SRLFindPositionNext(struct seqRangeList *rangeList, unsigned long pos,
                    seqRangeListSearchHint *hint)
{

  seqRangeListSearchHint hintCopy;
  size_t numRanges;
  struct seqRange *ranges;
  unsigned symBits;
  gt_assert(rangeList);
  ranges = rangeList->ranges;
  symBits = rangeList->symBits;
  if (hint)
    hintCopy = *hint;
  else
    gt_SRLInitListSearchHint(rangeList, &hintCopy);
  if ((numRanges = rangeList->numRanges) == 0)
  {
    return NULL;
  }
  if (ranges[0].startPos >= pos
      || pos < ranges[0].startPos + seqRangeLen(ranges + 0, symBits))
  {
    return ranges + 0;
  }
  else if (hintCopy && rangeNextMatch(hintCopy))
  {
    return ranges + hintCopy;
  }
  else if ((numRanges > hintCopy + 1) && rangeNextMatch(hintCopy + 1))
  {
    ++hintCopy;
    if (hint)
      *hint = hintCopy;
    return rangeList->ranges + hintCopy;
  }
  else if (hintCopy && rangeNextMatch(hintCopy - 1))
  {
    --hintCopy;
    if (hint)
      *hint = hintCopy;
    return rangeList->ranges + hintCopy;
  }
  else if (numRanges > 2)
  {
    unsigned long searchPos = pos;
    struct seqRange *searchRes =
      gt_bsearch_data(&searchPos, rangeList->ranges + 1,
                      rangeList->numRanges - 1, sizeof (struct seqRange),
                      posSeqRangeNextCompare, rangeList);
    if (searchRes && hint)
      *hint = searchRes - rangeList->ranges;
    return searchRes;
  }
  else
    return NULL;
}
