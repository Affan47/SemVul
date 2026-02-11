Close(void)
{

  SetCECInitialised(false);


  DELETE_AND_NULL(m_connCheck);
  StopThread(-1);
  m_inBuffer.Broadcast();
  StopThread();


  CLockObject lock(m_mutex);
  DELETE_AND_NULL(m_communication);
}
