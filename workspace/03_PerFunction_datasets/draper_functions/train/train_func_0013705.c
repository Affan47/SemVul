setDrivingState(char new3State)
{
  bDrivingState = (new3State=='1' || new3State=='W');

  if(m_monitor)
    m_monitor->setDrivingState(new3State);

}
