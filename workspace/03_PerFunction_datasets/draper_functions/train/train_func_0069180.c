getLegend (unsigned int iCurve) const

{

  if (m_vecsLegend.size() > iCurve && m_vecbLegendSet[iCurve])

    return &m_vecsLegend[iCurve];

  else

    return NULL;

}
