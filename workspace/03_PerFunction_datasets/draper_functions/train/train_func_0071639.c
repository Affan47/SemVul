StartOptimization(bool  )
{


  Superclass::StartOptimization();


  unsigned int numberOfParameters = m_Metric->GetNumberOfParameters();

  if ( this->GetInitialPosition().Size() < numberOfParameters )
    {
    this->SetInitialPosition( m_Metric->GetParameters() );
    }

  if ( m_LowerBound.size() < numberOfParameters && !m_BoundSelection.is_zero() )
    {
    itkExceptionMacro(<< "LowerBound array does not have sufficient number of elements");
    }

  if ( m_UpperBound.size() < numberOfParameters && !m_BoundSelection.is_zero() )
    {
    itkExceptionMacro(<< "UppperBound array does not have sufficient number of elements");
    }

  if ( m_BoundSelection.size() < numberOfParameters )
    {
    itkExceptionMacro(<< "BoundSelection array does not have sufficient number of elements");
    }

  if(this->m_CostFunctionConvergenceFactor == 0.0 && this->m_GradientConvergenceTolerance == 0.0)
    {
    itkExceptionMacro("LBFGSB Optimizer cannot function if both CostFunctionConvergenceFactor"
                      " and ProjectedGradienctTolerance are zero.");
    }

  ParametersType parameters( this->GetInitialPosition() );

  this->InvokeEvent( StartEvent() );


  m_VnlOptimizer->minimize(parameters);

  if ( parameters.GetSize() != this->GetInitialPosition().Size() )
    {

    this->m_Metric->SetParameters( this->GetInitialPosition() );
    itkExceptionMacro(<< "Error occurred in optimization");
    }

  this->m_Metric->SetParameters( parameters );

  this->InvokeEvent( EndEvent() );
}
