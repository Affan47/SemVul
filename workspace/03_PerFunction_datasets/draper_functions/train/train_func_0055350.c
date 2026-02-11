trimBuffer()
{
  if ( m_position < 4096 ) {
    return;
  }
  m_data = m_data.right( m_data.size() - m_position );
  m_position = 0;
}
