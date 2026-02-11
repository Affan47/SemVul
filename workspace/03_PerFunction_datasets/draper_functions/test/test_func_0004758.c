getNext(UKBYTE &b)
{
  if (m_readAhead) {
    m_readAhead = 0;
    b = m_readByte;
    m_lastIsAhead = 1;
    return 1;
  }

  m_lastIsAhead = 0;
  b = fgetc(m_file);
  return (!feof(m_file));
}
