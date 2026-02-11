PowerOn(const cec_logical_address initiator)
{
  bool bReturn(false);
  GetVendorId(initiator);

  MarkBusy();
  cec_power_status currentStatus;
  if (m_iLogicalAddress == CECDEVICE_TV ||
      ((currentStatus = GetPowerStatus(initiator, false)) != CEC_POWER_STATUS_IN_TRANSITION_STANDBY_TO_ON &&
        currentStatus != CEC_POWER_STATUS_ON))
  {
    LIB_CEC->AddLog(CEC_LOG_NOTICE, "<< powering on '%s' (%X)", GetLogicalAddressName(), m_iLogicalAddress);
    bReturn = m_handler->PowerOn(initiator, m_iLogicalAddress);
  }
  else
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "'%s' (%X) is already '%s'", GetLogicalAddressName(), m_iLogicalAddress, ToString(currentStatus));
  }

  MarkReady();
  return bReturn;
}
