GetValue() const
{
  ParametersType parameters = this->GetCurrentPosition();
  const unsigned int numberOfParameters = parameters.Size();
  SingleValuedNonLinearVnlOptimizer::CostFunctionAdaptorType *costFunction =
    this->GetNonConstCostFunctionAdaptor();

  if( costFunction != NULL )
    {
    if( static_cast<unsigned int>(costFunction->get_number_of_unknowns()) !=
        numberOfParameters )
      {
      itkExceptionMacro(<< "cost function and current position dimensions mismatch");
      }
    }
  else
    {
    itkExceptionMacro(<< "cost function not set");
    }

  if ( m_ScalesInitialized )
    {
    const ScalesType scales = this->GetScales();
    for ( unsigned int i = 0; i < numberOfParameters; i++ )
      {
      parameters[i] *= scales[i];
      }
    }
  return costFunction->f( parameters );
}
