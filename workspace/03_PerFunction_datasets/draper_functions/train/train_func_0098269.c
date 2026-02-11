GuessParameters(
  SizeValueType numberOfGradientEstimates,
  double initialStepSize)
{

  this->SetA(static_cast< double >( this->GetMaximumNumberOfIterations() ) / 10.0);

  if ( !m_CostFunction )
    {
    itkExceptionMacro(<< "No objective function defined! ");
    }


  const unsigned int spaceDimension =
    m_CostFunction->GetNumberOfParameters();


  const ParametersType & initialPosition  = this->GetInitialPosition();
  if ( spaceDimension != initialPosition.GetSize() )
    {
    itkExceptionMacro(<< "Number of parameters not correct!");
    }


  DerivativeType averageAbsoluteGradient(spaceDimension);
  averageAbsoluteGradient.Fill(0.0);
  m_CurrentIteration = 0;
  for ( SizeValueType n = 1; n <= numberOfGradientEstimates; ++n )
    {
    this->ComputeGradient(initialPosition, m_Gradient);
    for ( unsigned int j = 0; j < spaceDimension; j++ )
      {
      averageAbsoluteGradient[j] += std::fabs(m_Gradient[j]);
      }
    }
  averageAbsoluteGradient /= static_cast< double >( numberOfGradientEstimates );


  this->SetSa( initialStepSize * std::pow(m_A + 1.0, m_Alpha)
               / averageAbsoluteGradient.max_value() );
}
