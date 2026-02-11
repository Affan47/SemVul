GetAdapterProductId(void) const
{
  uint32_t iBuildDate(0);
  if (m_commands)
    iBuildDate = m_commands->GetPersistedBuildDate();

  return iBuildDate >= CEC_FW_DATE_DESCRIPTOR2 ? CEC_PID2 : CEC_PID;
}
