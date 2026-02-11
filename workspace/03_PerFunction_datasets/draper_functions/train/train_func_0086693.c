AdvanceOneStep(void)
{
  const double direction = ( m_Maximize ) ? 1.0 : -1.0;
  const ScalesType & scales = this->GetScales();

  const unsigned int spaceDimension =  m_CostFunction->GetNumberOfParameters();


  if ( scales.size() != spaceDimension )
    {
    itkExceptionMacro(<< "The size of Scales is "
                      << scales.size()
                      << ", but the NumberOfParameters is "
                      << spaceDimension
                      << ".");
    }

  DerivativeType transformedGradient(spaceDimension);
  for ( unsigned int i = 0; i < spaceDimension; i++ )
    {
    transformedGradient[i] = m_Gradient[i] / scales[i];
    }

  ParametersType currentPosition = this->GetCurrentPosition();


  vnl_quaternion< double > newQuaternion;
  for ( unsigned int j = 0; j < 4; j++ )
    {
    newQuaternion[j] = currentPosition[j] + direction * m_LearningRate
                       * transformedGradient[j];
    }

  newQuaternion.normalize();

  ParametersType newPosition(spaceDimension);

  for ( unsigned int j = 0; j < 4; j++ )
    {
    newPosition[j] = newQuaternion[j];
    }


  for ( unsigned int j = 4; j < spaceDimension; j++ )
    {
    newPosition[j] = currentPosition[j]
                     + direction * m_LearningRate * transformedGradient[j];
    }


  this->InvokeEvent( IterationEvent() );

  this->SetCurrentPosition(newPosition);
}
