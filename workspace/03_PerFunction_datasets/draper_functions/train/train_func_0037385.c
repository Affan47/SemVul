Create(uint64_t iInitialSize) {
#ifdef _WIN32
  m_StreamFile = CreateFileA(m_strFilename.c_str(),
                             GENERIC_READ | GENERIC_WRITE, 0, NULL,
                             CREATE_ALWAYS, 0, NULL);
  m_bIsOpen = m_StreamFile != INVALID_HANDLE_VALUE;
#else
  m_StreamFile = fopen(m_strFilename.c_str(), "w+b");
  m_bIsOpen = m_StreamFile != NULL;
#endif

  if (m_bIsOpen && iInitialSize>0) {
    SeekPos(iInitialSize-1);
    WriteData<unsigned char>(0,false);
    SeekStart();
  }

  m_bWritable = m_bIsOpen;

  return m_bIsOpen;
}
