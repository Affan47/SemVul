Close()
{
  IN_WRITE_BEGIN

  if (m_fd != -1) {
    RemoveAll();
    close(m_fd);
    m_fd = -1;
  }

  IN_WRITE_END
}
