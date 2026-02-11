fileWrite (const char* const filename)
{
  m_filename = filename;

  frnetorderstream fs (m_filename.c_str(), std::ios::out | std::ios::in | std::ios::trunc | std::ios::binary);
  if (fs.fail()) {
    sys_error (ERR_WARNING, "Error opening file %s for writing [fileCreate]", m_filename.c_str());
    return false;
  }
  if (! headerWrite(fs))
    return false;

  if (! arrayDataWrite (fs))
    return false;

  if (! labelsWrite (fs))
    return false;

  return true;
}
