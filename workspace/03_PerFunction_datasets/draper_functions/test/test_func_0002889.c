GetStatus(bool bForcePoll , bool bSuppressPoll )
{
  if (m_iLogicalAddress == CECDEVICE_BROADCAST)
    return CEC_DEVICE_STATUS_NOT_PRESENT;

  cec_bus_device_status status(CEC_DEVICE_STATUS_UNKNOWN);
  bool bNeedsPoll(false);

  {
    CLockObject lock(m_mutex);
    status = m_deviceStatus;
    bNeedsPoll = !bSuppressPoll &&
        m_deviceStatus != CEC_DEVICE_STATUS_HANDLED_BY_LIBCEC &&

            (bForcePoll ||

            m_deviceStatus == CEC_DEVICE_STATUS_UNKNOWN ||

            (m_deviceStatus == CEC_DEVICE_STATUS_NOT_PRESENT && m_iLogicalAddress == CECDEVICE_TV));
  }

  if (bNeedsPoll)
  {
    bool bPollAcked(false);
    if (bNeedsPoll)
      bPollAcked = m_processor->PollDevice(m_iLogicalAddress);

    status = bPollAcked ? CEC_DEVICE_STATUS_PRESENT : CEC_DEVICE_STATUS_NOT_PRESENT;
    SetDeviceStatus(status);
  }

  return status;
}
