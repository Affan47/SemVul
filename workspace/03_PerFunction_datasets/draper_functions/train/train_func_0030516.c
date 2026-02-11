AdvanceOneStep(void)
{
  itkDebugMacro("AdvanceOneStep");


  double direction;
  if ( this->m_Maximize )
    {
    direction = 1.0;
    }
  else
    {
    direction = -1.0;
    }


  const unsigned int spaceDimension =
    m_CostFunction->GetNumberOfParameters();


  ParametersType         newPosition(spaceDimension);
  const ParametersType & currentPosition = this->GetCurrentPosition();


  try
    {
    this->ComputeGradient(currentPosition, m_Gradient);
    }
  catch ( ExceptionObject & err )
    {


    m_StopCondition = MetricError;
    StopOptimization();

    throw err;
    }


  const double ak = this->Compute_a(m_CurrentIteration);

  m_LearningRate = ak;


  newPosition = currentPosition + ( direction * ak ) * m_Gradient;
  this->SetCurrentPosition(newPosition);


  m_GradientMagnitude = m_Gradient.magnitude();


  m_StateOfConvergence += ak * m_GradientMagnitude;
}
