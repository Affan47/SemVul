CanPersistConfiguration(void)
{
  return m_communication ? m_communication->GetFirmwareVersion() >= 2 : false;
}
