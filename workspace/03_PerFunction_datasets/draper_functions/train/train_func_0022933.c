Add(unsigned long a, unsigned long b)
{


  std::pair< Iterator, bool > result;
  if ( a == b ) { return false; }
  result = m_HashMap.insert( ValueType(a, b) );

  return result.second;
}
