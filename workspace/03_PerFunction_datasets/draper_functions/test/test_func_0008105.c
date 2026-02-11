displayBlockEncBlock(const EISeq *seq, unsigned long pos, FILE *fp,
                     EISHint hint)
{
  const struct blockCompositionSeq *seqIdx;
  int outCount;
  unsigned long bucketNum;
  gt_assert(seq && seq->classInfo == &blockCompositionSeqClass);
  seqIdx = constEncIdxSeq2blockCompositionSeq(seq);
  bucketNum = bucketNumFromPos(seqIdx, pos);
  outCount = printBucket(seqIdx, bucketNum, BUCKET_PRINT_BITSTRING_SEPARATOR
                         | BUCKET_PRINT_BITSTRING | BUCKET_PRINT_BITSIZES
                         | BUCKET_PRINT_RANGES_OVERLAY, fp, hint);
  return outCount;
}
