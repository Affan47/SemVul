stop()
{
  m_seek_percent = -1;
  strcpy(m_file, "");
  m_state = STOPPED;
  m_elapsed = m_remaining = 0;
  if (m_thread) pthread_join(m_thread, 0);
  m_thread = 0;
  if (m_decoder) {
    m_decoder->close();
    m_decoder = 0;
  }
}
