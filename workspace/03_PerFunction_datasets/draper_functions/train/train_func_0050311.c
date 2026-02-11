ElementData(METAIO_STL::streamoff _i, double _v)
  {
  if(_i<m_Quantity)
    {
    MET_DoubleToValue(_v, m_ElementType, m_ElementData, _i);
    return true;
    }
  return false;
  }
