unmatchedAtEnd(byte* const buf,
    const size_t bufferLength, const size_t data, Desc& desc) {
  Paranoid(unmatchedStart < off);


  const PartialMatch* y = matches->findStartOffset(unmatchedStart);
  if (y != 0 && y->startOffset() < off - bufferLength) {
    unmatchedStart = off - bufferLength;
    debugRangeInfo(y->startOffset(), unmatchedStart,
                   "UNMATCHED at end, re-reading partial match from", y);
    size_t toReread = unmatchedStart - y->startOffset();
    desc.unmatchedData(toReread);
    if (rereadUnmatched(y->file(), toReread))
      return FAILURE;
  }

  if (unmatchedStart < off) {
    debugRangeInfo(unmatchedStart, off, "UNMATCHED at end");
    size_t toWrite = off - unmatchedStart;
    Assert(toWrite <= bufferLength);
    size_t writeStart = modSub(data, toWrite, bufferLength);
    writeBuf(buf, writeStart, data, bufferLength, zip);
    desc.unmatchedData(toWrite);
    unmatchedStart = off;
  }
  return SUCCESS;
}
