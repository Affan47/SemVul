compute(const InternalParametersType   & x,
          InternalMeasureType      *fun,
          InternalDerivativeType   *g)
{

  ParametersType parameters( x.size() );
  double         measure;

  if ( m_ScalesInitialized )
    {
    const ScalesType & invScales = this->GetInverseScales();
    for ( unsigned int i = 0; i < parameters.size(); i++ )
      {
      parameters[i] = x[i] * invScales[i];
      }
    }
  else
    {
    parameters.SetDataSameSize( const_cast< double * >( x.data_block() ), false );
    }

  m_CostFunction->GetValueAndDerivative(parameters, measure, m_CachedDerivative);
  if ( g )
    {
    this->ConvertExternalToInternalGradient(m_CachedDerivative, *g);
    }
  if ( fun )
    {
    if ( !m_NegateCostFunction )
      {
      *fun = static_cast< InternalMeasureType >( measure );
      }
    else
      {
      *fun = static_cast< InternalMeasureType >( -measure );
      }


    m_CachedValue = *fun;
    }
  m_CachedCurrentParameters = parameters;
  this->ReportIteration( FunctionAndGradientEvaluationIterationEvent() );
}
