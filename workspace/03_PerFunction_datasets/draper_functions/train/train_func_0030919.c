printBlockEncPosDiags(const EISeq *seq, unsigned long pos, FILE *fp,
                      EISHint hint)
{
  const struct blockCompositionSeq *seqIdx;
  int outCount = 0;
  unsigned long bucketNum;
  gt_assert(seq && seq->classInfo == &blockCompositionSeqClass);
  seqIdx = constEncIdxSeq2blockCompositionSeq(seq);
  bucketNum = bucketNumFromPos(seqIdx, pos);
  fputs("##################################################\n"
        "# This bucket:\n"
        "##################################################\n", fp);
  outCount += printBucket(seqIdx, bucketNum, BUCKET_PLAIN, fp, hint);
  if (bucketNum)
  {
    fputs("##################################################\n"
          "# Previous bucket:\n"
          "##################################################\n", fp);
    outCount += printBucket(seqIdx, bucketNum - 1, BUCKET_PLAIN, fp, hint);
  }
  if (bucketNum < bucketNumFromPos(seqIdx, EISLength(seq)))
  {
    fputs("##################################################\n"
          "# Next bucket:\n"
          "##################################################\n", fp);
    outCount += printBucket(seqIdx, bucketNum + 1, BUCKET_PLAIN, fp, hint);
  }
  return outCount;
}
