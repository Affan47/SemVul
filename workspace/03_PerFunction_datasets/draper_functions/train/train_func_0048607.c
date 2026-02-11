ResumeOptimization(void)
{
  itkDebugMacro("ResumeOptimization");

  m_Stop = false;

  m_StopConditionDescription.str("");
  m_StopConditionDescription << this->GetNameOfClass() << ": ";
  InvokeEvent( StartEvent() );
  while ( !m_Stop )
    {
    try
      {
      m_CostFunction->GetValueAndDerivative(
        this->GetCurrentPosition(), m_Value, m_Gradient);
      }
    catch ( ExceptionObject & err )
      {


      m_StopCondition = MetricError;
      m_StopConditionDescription << "Metric error";
      StopOptimization();


      throw err;
      }

    if ( m_Stop )
      {
      m_StopConditionDescription << "StopOptimization() called";
      break;
      }

    AdvanceOneStep();

    m_CurrentIteration++;

    if ( m_CurrentIteration >= m_NumberOfIterations )
      {
      m_StopConditionDescription << "Maximum number of iterations ("
                                 << m_NumberOfIterations
                                 << ") exceeded.";
      m_StopCondition = MaximumNumberOfIterations;
      StopOptimization();
      break;
      }
    }
}
