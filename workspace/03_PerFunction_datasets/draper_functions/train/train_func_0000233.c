Initialize()
{
  SizeValueType i, low, high;


  low = 0; high = 0;

  SizeValueType noOfClasses = static_cast< SizeValueType >( m_Targets.size() );

  for ( i = 0; i < noOfClasses; i++ )
    {
    if ( m_Targets[i].GetMean() > m_Targets[high].GetMean() )
      {
      high = i;
      }
    if ( m_Targets[i].GetMean() < m_Targets[low].GetMean() )
      {
      low = i;
      }
    }

  m_LowerBound = m_Targets[low].GetMean() - 9.0 * m_Targets[low].GetSigma();
  m_UpperBound = m_Targets[high].GetMean() + 9.0 * m_Targets[high].GetSigma();

  CreateCache(m_LowerBound, m_UpperBound, 1000000);
}
