AnatomicalOrientationAcronym(void) const
  {
  int i;
  for(i=0; i<m_NDims; i++)
    {
    m_OrientationAcronym[i] = MET_OrientationTypeName[m_AnatomicalOrientation[i]][0];
    }
  m_OrientationAcronym[i] = '\0';
  return m_OrientationAcronym;
  }
