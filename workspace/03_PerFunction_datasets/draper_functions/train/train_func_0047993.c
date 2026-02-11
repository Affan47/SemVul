MakeKey(const std::string& f,
    const std::string& e,
    const std::string& c) const
{
  std::string key;
  if(!f.empty())
  {
    key += f;
  }
  if(!m_FactorsE.empty())
  {
    if(!key.empty())
    {
      key += " ||| ";
    }
    key += e;
  }
  if(!m_FactorsC.empty())
  {
    if(!key.empty())
    {
      key += " ||| ";
    }
    key += c;
  }
  key += " ||| ";
  return key;
}
