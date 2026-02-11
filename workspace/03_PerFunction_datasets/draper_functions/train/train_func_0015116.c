reset_all ()
{
  m_chardata_length = 0;


  if (!grow (m_chardata_buffer, m_chardata_length, m_chardata_max, 64)) return false;


  return true;
}
