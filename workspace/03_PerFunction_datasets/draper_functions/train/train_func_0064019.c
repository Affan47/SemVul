_newline()
{
  if( !m_newline ){
    fprintf(m_stream, "\n");
    m_newline = 1;
  }
}
