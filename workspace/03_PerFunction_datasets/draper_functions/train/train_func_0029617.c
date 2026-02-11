ScaleSolution(Float scale, unsigned int solutionIndex)
{

  if( scale == 1.0 )
    {
    return;
    }

  unsigned int i;
  for( i = 0; i < m_Order; i++ )
    {
    this->SetSolutionValue(i, scale * GetSolutionValue(i, solutionIndex), solutionIndex);
    }

  return;
}
