addRangeEncodedSyms(struct seqRangeList *rangeList, const Symbol *block,
                    unsigned blockSize, unsigned long blockNum,
                    const MRAEnc *alphabet, int selection, const int *rangeSel)
{
  unsigned i;
  for (i = 0; i < blockSize; ++i)
  {
    gt_assert(gt_MRAEncSymbolIsInSelectedRanges(alphabet, block[i],
                                          selection, rangeSel) >= 0);
    if (gt_MRAEncSymbolIsInSelectedRanges(alphabet, block[i], selection,
                                          rangeSel)) {
      gt_SRLAddPosition(rangeList, blockNum * blockSize + i, block[i]);
    }
  }
}
