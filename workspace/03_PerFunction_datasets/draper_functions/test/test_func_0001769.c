ElementData(int _i, double _v)
  {
  if(_i<m_Length*m_ElementNumberOfChannels)
    {
    MET_DoubleToValue(_v, m_ElementType, m_ElementData, _i);
    return true;
    }
  return false;
  }
