album()
{
  if (m_album && m_album[0]) return m_album;
  if (m_decoder) return m_decoder->album();
  return NULL;
}
