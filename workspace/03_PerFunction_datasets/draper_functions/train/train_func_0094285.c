StartOptimization(void)
{
  itkDebugMacro("StartOptimization");

  if ( !m_CostFunction )
    {
    itkExceptionMacro(<< "No objective function defined! ");
    }


  const unsigned int spaceDimension =
    m_CostFunction->GetNumberOfParameters();
  if ( spaceDimension != this->GetInitialPosition().GetSize() )
    {
    itkExceptionMacro(<< "Number of parameters not correct!");
    }

  m_CurrentIteration = 0;
  m_StopCondition = Unknown;
  m_StateOfConvergence = 0.0;

  this->SetCurrentPosition( this->GetInitialPosition() );
  this->ResumeOptimization();
}
