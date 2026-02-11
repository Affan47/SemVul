GetVariate()
{
  if ( --m_Gaussfaze )
    {
    return m_GScale * m_Gausssave[m_Gaussfaze];
    }
  else
    {
    return FastNorm();
    }
}
