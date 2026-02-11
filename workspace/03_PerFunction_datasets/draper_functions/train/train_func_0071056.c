SyncNewlines(int master)
{
  for( int i=0; i < O_NCHANNELS; i++ ){
    if( i != master && m_streams[i]->SameDev(m_streams[master]) )
      m_streams[i]->SyncNewline(m_streams[master]);
  }
}
