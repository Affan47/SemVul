Unlock()
{
  if (!m_fLocked)
    return;

  if (unlink(m_path.c_str()) != 0 && errno != ENOENT)
    throw AppInstException(errno);

  m_fLocked = false;
}
