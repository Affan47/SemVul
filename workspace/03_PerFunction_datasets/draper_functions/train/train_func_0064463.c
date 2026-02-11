AllocateTemp(const string& strTempFile, bool bBuildOffsetTables) {
  CleanupTemp();

  uint64_t iDataSize = (bBuildOffsetTables) ? ComputeDataSizeAndOffsetTables(): ComputeDataSize();

  m_pTempFile = LargeRAWFile_ptr(new LargeRAWFile(strTempFile));
  if (!m_pTempFile->Create(iDataSize)) {
    m_pTempFile.reset();
    throw "Unable To create Temp File";
  }
}
