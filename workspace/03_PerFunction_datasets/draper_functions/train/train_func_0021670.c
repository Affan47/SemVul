gt_reads2twobit_write_encoded_nocodesshift(GtReads2Twobit *r2t,
    GtTwobitencoding *outputbuffer, GtTwobitencoding offset,
    unsigned long firstcodeidx, unsigned long lastcodeidx)
{
  if (offset == 0)
    outputbuffer[0] = r2t->twobitencoding[firstcodeidx];
  else
  {
    GtTwobitencoding mask;
    mask =
      ((GtTwobitencoding)1 << GT_MULT2(GT_UNITSIN2BITENC - offset)) - 1;
    outputbuffer[0] =
      (r2t->twobitencoding[firstcodeidx] & mask) |
      (outputbuffer[0] & ~mask);
  }
  if (lastcodeidx > firstcodeidx)
    memcpy(outputbuffer + 1, r2t->twobitencoding + firstcodeidx + 1,
        sizeof (GtTwobitencoding) * (lastcodeidx - firstcodeidx));
}
