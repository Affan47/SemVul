Open(bool bMustBeSameVersion, bool bVerify, bool bReadWrite, std::string* pstrProblem) {
  if (m_bFileIsLoaded) return true;

  m_bFileIsLoaded = m_streamFile->Open(bReadWrite);

  if (!m_bFileIsLoaded) {
    if (pstrProblem) (*pstrProblem) = "file not found or access denied";
    return false;
  }
  m_bFileIsReadWrite = bReadWrite;

  if (ParseGlobalHeader(bVerify,pstrProblem)) {
    if (bMustBeSameVersion && ms_ulReaderVersion != m_GlobalHeader.ulFileVersion) {
      if (pstrProblem) (*pstrProblem) = "wrong UVF file version";
      return false;
    }
    ParseDataBlocks();
    return true;
  } else {
    Close();
    return false;
  }
}
