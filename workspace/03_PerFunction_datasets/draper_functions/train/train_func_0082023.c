WriteEEPROM(void)
{
  {
    CLockObject lock(m_mutex);
    if (!m_bNeedsWrite)
      return true;
  }

  LIB_CEC->AddLog(CEC_LOG_DEBUG, "writing settings in the EEPROM");

  CCECAdapterMessage params;
  CCECAdapterMessage *message = m_comm->SendCommand(MSGCODE_WRITE_EEPROM, params);
  bool bReturn = message && message->state == ADAPTER_MESSAGE_STATE_SENT_ACKED;
  DELETE_AND_NULL(message);

  if (bReturn)
  {
    CLockObject lock(m_mutex);
    m_bNeedsWrite = false;
  }

  return bReturn;
}
