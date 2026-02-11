readLocateInfoHeader(EISeq *seqIdx, struct locateHeader *headerData)
{
  FILE *fp;
  gt_assert(seqIdx && headerData);
  if (!(fp = EISSeekToHeader(seqIdx, LOCATE_INFO_IN_INDEX_HEADERID, NULL)))
    return 0;
  if (fread(headerData, sizeof (*headerData), 1, fp) != 1)
    return 0;
  return 1;
}
