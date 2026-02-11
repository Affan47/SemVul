gt_reads2twobit_zeropad_tbe(GtReads2Twobit *r2t)
{
  unsigned long pos, codenum, posincode, shift;
  pos = r2t->total_seqlength - 1UL;
  codenum = GT_DIVBYUNITSIN2BITENC(pos);
  posincode = GT_MODBYUNITSIN2BITENC(pos);
  if (posincode < (unsigned long)GT_UNITSIN2BITENC - 1UL)
  {
    shift = GT_MULT2(GT_UNITSIN2BITENC - 1UL - posincode);
    r2t->twobitencoding[codenum] =
      (GtTwobitencoding)((r2t->twobitencoding[codenum] >> shift) << shift);
  }
  r2t->twobitencoding[codenum + 1UL] = 0;
}
