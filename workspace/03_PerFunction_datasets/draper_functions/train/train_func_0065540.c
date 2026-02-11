oneStep()
{
  m_pTimers->start("OneStepForceAndExchange");
  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CMPIBarrier barrier(m_global_comm);

  m_pTimers->start("ForceCalculation");
  cmd_buffer.broadcast(CMD_CALC);
  barrier.wait("oneStep.1");
  m_pTimers->stop("ForceCalculation");

  m_pTimers->start("BoundaryDataExchange");
  cmd_buffer.broadcast(CMD_XCHANGE);
  barrier.wait("oneStep.2");
  m_pTimers->stop("BoundaryDataExchange");

  console.Debug() << "=== TIME STEP ===\n";

  console.Timing() << "Force calculation  " << m_pTimers->getTiming("ForceCalculation") << "\n";
  console.Timing() << "Boundary exchange  " << m_pTimers->getTiming("BoundaryDataExchange") << "\n";
  m_pTimers->stop("OneStepForceAndExchange");
  console.Timing() << "one step           " << m_pTimers->getTiming("OneStepForceAndExchange") << "\n";

}
