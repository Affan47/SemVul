atCommandEnd()
{
  int savedPos = m_position;
  do {
    if ( !waitForMoreData( m_position >= m_data.length() ) ) {
      throw ImapParserException( "Unable to read more data" );
    }
    stripLeadingSpaces();
  } while ( m_position >= m_data.size() );

  if ( m_data.at( m_position ) == '\n' || m_data.at( m_position ) == '\r' ) {
    if ( m_data.at( m_position ) == '\r' ) {
      ++m_position;
    }
    if ( m_position < m_data.length() && m_data.at( m_position ) == '\n' ) {
      ++m_position;
    }


    trimBuffer();

    return true;
  }
  m_position = savedPos;
  return false;
}
