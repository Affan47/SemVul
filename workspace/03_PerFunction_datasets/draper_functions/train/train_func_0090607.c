GetHash(const char* key)
{
  std::string keyStr(key);
  size_t i = std::distance(m_landmarks.begin(),
      std::upper_bound(m_landmarks.begin(),
      m_landmarks.end(), keyStr)) - 1;

  if(i == 0ul-1)
    return GetSize();

  size_t pos = GetHash(i, key);
  if(pos != GetSize())
    return (1ul << m_orderBits) * i + pos;
  else
    return GetSize();
}
