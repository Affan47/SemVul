Calc_ToPitch()
{
   int nSemitonesChange =
      (int)(m_dSemitonesChange + ((m_dSemitonesChange < 0.0) ? -0.5 : 0.5));
   m_nToPitch = (m_nFromPitch + nSemitonesChange) % 12;
   if (m_nToPitch < 0)
      m_nToPitch += 12;
}
