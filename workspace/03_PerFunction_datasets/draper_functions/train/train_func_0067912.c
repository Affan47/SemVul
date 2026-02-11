findMaxMerge(const Word16 mergeGainLookUp[MAX_SFB_LONG],
             const SECTION_INFO *sectionInfo,
             const Word16 maxSfb, Word16 *maxNdx)
{
  Word32 i, maxMergeGain;
  maxMergeGain = 0;

  for (i=0; i+sectionInfo[i].sfbCnt < maxSfb; i += sectionInfo[i].sfbCnt) {

    if (mergeGainLookUp[i] > maxMergeGain) {
      maxMergeGain = mergeGainLookUp[i];
      *maxNdx = i;
    }
  }
  return extract_l(maxMergeGain);
}
