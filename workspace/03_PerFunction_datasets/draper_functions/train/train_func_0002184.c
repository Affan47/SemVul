checkMD5Match_mismatch(const size_t stillBuffered,
                                        PartialMatch* x, Desc& desc) {
  const PartialMatch* oldestMatch = matches->findLowestStartOffset();
  uint64 rereadEnd = off - stillBuffered;
  uint64 xStartOffset = x->startOffset();
  if (x != oldestMatch || xStartOffset >= rereadEnd) {

    matches->eraseFront();
    return SUCCESS;
  }


  FilePart* xfile = x->file();
  Assert(matches->front() == x);
  matches->eraseFront();
  if (!matches->empty()) {

    const PartialMatch* newOldestMatch = matches->findLowestStartOffset();
    if (rereadEnd > newOldestMatch->startOffset())
      rereadEnd = newOldestMatch->startOffset();
  }
  debugRangeInfo(xStartOffset, rereadEnd,
                 "UNMATCHED after some blocks, re-reading from", x);

  desc.unmatchedData(rereadEnd - xStartOffset);
  unmatchedStart = rereadEnd;

  uint64 bytesToWrite = rereadEnd - xStartOffset;
  return rereadUnmatched(xfile, bytesToWrite);
}
