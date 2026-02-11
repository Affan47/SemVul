Initialize(double initialRadius, double grow, double shrink)
{
  m_InitialRadius = initialRadius;

  if ( grow == -1 )
    {
    m_GrowthFactor = 1.05;
    }
  else
    {
    m_GrowthFactor = grow;
    }
  if ( shrink == -1 )
    {
    m_ShrinkFactor = vcl_pow(m_GrowthFactor, -0.25);
    }
  else
    {
    m_ShrinkFactor = shrink;
    }
}
