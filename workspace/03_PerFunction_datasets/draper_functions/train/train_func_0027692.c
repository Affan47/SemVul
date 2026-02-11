gradf(const InternalParametersType   & inparameters,
        InternalDerivativeType   & gradient)
{
  if ( !m_CostFunction )
    {
    itkGenericExceptionMacro("Attempt to use a SingleValuedVnlCostFunctionAdaptor without any CostFunction plugged in");
    }


  ParametersType parameters( inparameters.size() );
  if ( m_ScalesInitialized )
    {
    const ScalesType & invScales = this->GetInverseScales();
    for ( unsigned int i = 0; i < parameters.size(); i++ )
      {
      parameters[i] = inparameters[i] * invScales[i];
      }
    }
  else
    {
    parameters.SetDataSameSize( const_cast< double * >( inparameters.data_block() ), false );
    }

  m_CostFunction->GetDerivative(parameters, m_CachedDerivative);
  this->ConvertExternalToInternalGradient(m_CachedDerivative, gradient);


  m_CachedCurrentParameters = parameters;
  this->ReportIteration( GradientEvaluationIterationEvent() );
}
