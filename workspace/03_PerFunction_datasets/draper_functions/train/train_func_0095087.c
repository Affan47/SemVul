GetChild(Word &wordFound, UINT64 &childFilePos, size_t ind, OnDiskWrapper &onDiskWrapper) const
{

  size_t wordSize = onDiskWrapper.GetSourceWordSize();
  size_t childSize = wordSize + sizeof(UINT64);

  char *currMem = m_memLoad
                  + sizeof(UINT64) * 2
                  + sizeof(float) * onDiskWrapper.GetNumCounts()
                  + childSize * ind;

  size_t memRead = ReadChild(wordFound, childFilePos, currMem);
  CHECK(memRead == childSize);
}
