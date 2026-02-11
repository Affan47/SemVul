checkRsyncSumMatch(const RsyncSum64& sum,
    const uint32& bitMask, const size_t blockLen, const size_t back,
    const size_t md5BlockLength, uint64& nextEvent) {

  typedef const vector<FilePart*> FVec;
  FVec& hashEntry = block[sum.getHi() & bitMask];
  if (hashEntry.empty()) return;

  FVec::const_iterator i = hashEntry.begin(), e = hashEntry.end();
  do {
    FilePart* file = *i;
    const RsyncSum64* fileSum = file->getRsyncSum(cache);
    if (fileSum != 0 && *fileSum == sum)

      checkRsyncSumMatch2(blockLen, back, md5BlockLength, nextEvent, file);
    ++i;
  } while (i != e);
  return;
}
