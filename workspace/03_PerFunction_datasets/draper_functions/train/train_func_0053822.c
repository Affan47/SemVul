PowerOn(const cec_logical_address iInitiator, const cec_logical_address iDestination)
{
  bool bCheck(false);
  bool bRetval(false);
  if (m_busDevice->GetCurrentPowerStatus() != CEC_POWER_STATUS_ON && (!m_powerOnCheck || !m_powerOnCheck->IsRunning()))
    bCheck = true;
  bRetval = CCECCommandHandler::PowerOn(iInitiator, iDestination);

  if (bRetval && bCheck)
  {
    if (!m_powerOnCheck)
      m_powerOnCheck = new CAQPowerStatusCheck(this, iInitiator, iDestination);
    if (m_powerOnCheck)
      m_powerOnCheck->CreateThread();
  }

  return bRetval;
}
