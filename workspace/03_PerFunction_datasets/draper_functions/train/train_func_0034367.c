Process(void)
{
  CCECBusDevice* tv = m_handler->m_processor->GetDevice(CECDEVICE_TV);
  cec_power_status status(CEC_POWER_STATUS_UNKNOWN);
  while (status != CEC_POWER_STATUS_ON)
  {
    m_event.Wait(TV_ON_CHECK_TIME_MS);
    if (!IsRunning())
      return NULL;

    status = tv->GetPowerStatus(m_handler->m_busDevice->GetLogicalAddress());

    if (status != CEC_POWER_STATUS_ON &&
        status != CEC_POWER_STATUS_IN_TRANSITION_STANDBY_TO_ON)
    {
      CLockObject lock(m_handler->m_mutex);
      tv->OnImageViewOnSent(false);
      m_handler->m_iActiveSourcePending = GetTimeMs();
    }
  }
  return NULL;
}
