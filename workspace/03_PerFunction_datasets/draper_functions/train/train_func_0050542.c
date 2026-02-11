TransmitActiveSource(bool bIsReply)
{
  bool bSendActiveSource(false);
  uint16_t iPhysicalAddress(CEC_INVALID_PHYSICAL_ADDRESS);

  {
    CLockObject lock(m_mutex);
    if (!HasValidPhysicalAddress())
    {
      LIB_CEC->AddLog(CEC_LOG_DEBUG, "%s (%X) has an invalid physical address (%04x), not sending active source commands", GetLogicalAddressName(), m_iLogicalAddress, m_iPhysicalAddress);
      return false;
    }

    iPhysicalAddress = m_iPhysicalAddress;

    if (m_powerStatus != CEC_POWER_STATUS_ON && m_powerStatus != CEC_POWER_STATUS_IN_TRANSITION_STANDBY_TO_ON)
      LIB_CEC->AddLog(CEC_LOG_DEBUG, "<< %s (%X) is not powered on", GetLogicalAddressName(), m_iLogicalAddress);
    else if (m_bActiveSource)
    {
      LIB_CEC->AddLog(CEC_LOG_NOTICE, "<< %s (%X) -> broadcast (F): active source (%4x)", GetLogicalAddressName(), m_iLogicalAddress, m_iPhysicalAddress);
      bSendActiveSource = true;
    }
    else
      LIB_CEC->AddLog(CEC_LOG_DEBUG, "<< %s (%X) is not the active source", GetLogicalAddressName(), m_iLogicalAddress);
  }

  bool bActiveSourceSent(false);
  if (bSendActiveSource)
  {
    MarkBusy();
    bActiveSourceSent = m_handler->TransmitActiveSource(m_iLogicalAddress, iPhysicalAddress, bIsReply);
    MarkReady();
  }

  return bActiveSourceSent;
}
