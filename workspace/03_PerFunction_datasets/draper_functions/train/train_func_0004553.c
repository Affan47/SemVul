SetLogicalAddress(const cec_logical_address iLogicalAddress)
{
  bool bReturn(true);

  if (GetPrimaryLogicalAdddress() != iLogicalAddress)
  {
    LIB_CEC->AddLog(CEC_LOG_NOTICE, "setting primary logical address to %1x", iLogicalAddress);
    {
      CLockObject lock(m_mutex);
      m_configuration.logicalAddresses.primary = iLogicalAddress;
      m_configuration.logicalAddresses.Set(iLogicalAddress);
    }

    bReturn = m_processor->RegisterClient(this);


    if (bReturn)
      PersistConfiguration(m_configuration);
  }

  return bReturn;
}
