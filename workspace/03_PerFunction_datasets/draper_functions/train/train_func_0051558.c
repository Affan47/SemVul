GetValue(const std::string& rKey, std::string& rVal)
{
  CFG_ITER it = m_values.find(rKey);
  if (it != m_values.end()) {
    rVal = (*it).second;
    return true;
  }

  it = m_defaults.find(rKey);
  if (it != m_defaults.end()) {
    rVal = (*it).second;
    return true;
  }

  return false;
}
