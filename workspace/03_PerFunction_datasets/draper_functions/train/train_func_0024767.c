posSeqRangeOverlapCompare(const void *key, const void *elem, void *data)
{
  unsigned long pos;
  const struct seqRange *range;
  const struct seqRangeList *rangeList;
  pos = *(const unsigned long *)key;
  range = elem;
  rangeList = data;
  if (pos < range->startPos)
    return -1;
  else if (pos >= range->startPos + seqRangeLen(range, rangeList->symBits))
    return 1;
  else
    return 0;
}
