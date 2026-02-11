blockCompSeqRank(struct encIdxSeq *eSeqIdx, Symbol eSym, unsigned long pos,
                 union EISHint *hint)
{
  struct blockCompositionSeq *seqIdx;
  unsigned long rankCount;
  gt_assert(eSeqIdx && eSeqIdx->classInfo == &blockCompositionSeqClass);
  seqIdx = encIdxSeq2blockCompositionSeq(eSeqIdx);
  gt_assert(gt_MRAEncSymbolIsInSelectedRanges(seqIdx->baseClass.alphabet,
                                        eSym, BLOCK_COMPOSITION_INCLUDE,
                                        seqIdx->modes) >= 0);
  if (gt_MRAEncSymbolIsInSelectedRanges(seqIdx->baseClass.alphabet, eSym,
                                     BLOCK_COMPOSITION_INCLUDE, seqIdx->modes))
  {
    BitOffset varDataMemOffset, cwIdxMemOffset;
    struct superBlock *sBlock;
    Symbol bSym = MRAEncMapSymbol(seqIdx->blockMapAlphabet, eSym);
    unsigned long blockNum, bucketNum;
    unsigned blockSize = seqIdx->blockSize, bitsPerCompositionIdx
      = seqIdx->compositionTable.compositionIdxBits;
    bucketNum = bucketNumFromPos(seqIdx, pos);
#ifdef USE_SBLOCK_CACHE
    sBlock = cacheFetchSuperBlock(seqIdx, bucketNum,
                                  &hint->bcHint.sBlockCache);
#else
    sBlock = fetchSuperBlock(seqIdx, bucketNum, NULL);
#endif
    rankCount = sBlockGetPartialSymSum(sBlock, bSym, seqIdx);
    blockNum = blockNumFromPos(seqIdx, pos);
    walkCompIndicesPrefix(
      seqIdx, sBlock, blockNum % seqIdx->bucketBlocks, cwIdxMemOffset,
      rankCount += symCountFromComposition(
        &seqIdx->compositionTable, seqIdx->blockMapAlphabetSize, compIndex,
        bSym);,
      varDataMemOffset);
    rankCount = adjustPosRankForBlock(
      seqIdx, sBlock, pos, bSym, blockSize, rankCount, cwIdxMemOffset,
      varDataMemOffset, bitsPerCompositionIdx);
    if (bSym == seqIdx->blockEncFallback)
    {
      unsigned long base = bucketBasePos(seqIdx, bucketNum);
      rankCount -= gt_SRLAllSymbolsCountInSeqRegion(
        seqIdx->rangeEncs, base, pos, &hint->bcHint.rangeHint);
    }
#ifndef USE_SBLOCK_CACHE
    deleteSuperBlock(sBlock);
#endif
  }
  else
  {
    rankCount = gt_SRLSymbolCountInSeqRegion(seqIdx->rangeEncs, 0, pos, eSym,
                                          &hint->bcHint.rangeHint);
  }
  return rankCount;
}
