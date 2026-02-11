StopOptimization(void)
{
  itkDebugMacro("StopOptimization");
  m_Stop = true;
  InvokeEvent( EndEvent() );
}
