nextRange(GtRange *range, GtSpecialrangeiterator *sri,
          GtReadmode readmode, unsigned long seqLastPos)
{
  bool hasNextRange = gt_specialrangeiterator_next(sri, range);
  if (hasNextRange)
  {
    if (GT_ISDIRREVERSE(readmode))
    {
      unsigned long temp = range->end;
      range->end = seqLastPos - range->start;
      range->start = seqLastPos - temp;
    }
  }
  else
    range->end = seqLastPos + 1, range->start = seqLastPos;
  return hasNextRange;
}
