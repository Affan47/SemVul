_GetNextTokenNoPrefix(std::string& rToken)
{
  const char* s = m_str.c_str();
  for (SIZE i=m_pos; i<m_len; i++) {
    if (s[i] == m_cDelim) {
      rToken = m_str.substr(m_pos, i - m_pos);
      m_pos = i + 1;
      return;
    }
  }

  rToken = m_str.substr(m_pos);
  m_pos = m_len;
}
