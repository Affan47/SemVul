setTimeStepSize(double dt)
{
  m_pCheckPointController->setTimeStepSize(dt);
  m_pSnapShotController->setTimeStepSize(dt);
  m_dt = dt;

  BroadcastCommand cmd(getGlobalRankAndComm(), CMD_SETTIMESTEPSIZE);
  cmd.append(m_dt);
  cmd.broadcast();
}
