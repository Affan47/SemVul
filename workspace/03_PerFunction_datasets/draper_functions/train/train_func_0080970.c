SetSystemAudioModeStatus(const cec_system_audio_status mode)
{
  CLockObject lock(m_mutex);
  if (m_systemAudioStatus != mode)
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, ">> %s (%X): system audio mode status changed from %s to %s", GetLogicalAddressName(), m_iLogicalAddress, ToString(m_systemAudioStatus), ToString(mode));
    m_systemAudioStatus = mode;
    return true;
  }

  return false;
}
