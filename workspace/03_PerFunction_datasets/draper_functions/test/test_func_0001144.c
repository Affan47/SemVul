ActivateSource(uint64_t iDelay )
{
  MarkAsActiveSource();
  MarkBusy();
  bool bReturn(true);
  if (iDelay == 0)
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "sending active source message for '%s'", ToString(m_iLogicalAddress));
    bReturn = m_handler->ActivateSource();
  }
  else
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "scheduling active source message for '%s'", ToString(m_iLogicalAddress));
    m_handler->ScheduleActivateSource(iDelay);
  }
  MarkReady();
  return bReturn;
}
