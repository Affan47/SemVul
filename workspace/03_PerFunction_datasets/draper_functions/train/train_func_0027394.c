SetDefaultStepLength(double f)
{
  if ( Math::ExactlyEquals(f, m_DefaultStepLength) )
    {
    return;
    }

  m_DefaultStepLength = f;
  if ( m_OptimizerInitialized )
    {
    m_VnlOptimizer->default_step_length = m_DefaultStepLength;
    }

  this->Modified();
}
