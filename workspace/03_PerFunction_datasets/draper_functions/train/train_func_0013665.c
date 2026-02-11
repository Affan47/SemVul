SetVariance(double variance)
{
  bool modified = false;

  if ( m_Parameters.GetSize() > 1 )
    {
    if ( Math::NotExactlyEquals(m_Parameters[1], variance) )
      {
      modified = true;
      }
    }

  if ( m_Parameters.GetSize() != 2 )
    {
    bool   cache = false;
    double t = 0.0;


    if ( m_Parameters.GetSize() > 0 )
      {
      t = m_Parameters[0];
      cache = true;
      }


    m_Parameters = ParametersType(2);


    if ( cache )
      {
      m_Parameters[0] = t;
      }
    else
      {
      m_Parameters[0] = 0.0;
      }

    modified = true;
    }

  m_Parameters[1] = variance;

  if ( modified )
    {
    this->Modified();
    }
}
