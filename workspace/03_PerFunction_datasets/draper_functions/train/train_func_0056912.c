TransmitSetMenuLanguage(const cec_logical_address destination, bool bIsReply)
{
  bool bReturn(false);
  cec_menu_language language;
  {
    CLockObject lock(m_mutex);
    language = m_menuLanguage;
  }

  char lang[4];
  {
    CLockObject lock(m_mutex);
    lang[0] = language.language[0];
    lang[1] = language.language[1];
    lang[2] = language.language[2];
    lang[3] = (char)0;
  }

  MarkBusy();
  if (lang[0] == '?' && lang[1] == '?' && lang[2] == '?')
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "<< %s (%X) -> %s (%X): menu language feature abort", GetLogicalAddressName(), m_iLogicalAddress, ToString(destination), destination);
    m_processor->TransmitAbort(m_iLogicalAddress, destination, CEC_OPCODE_GIVE_DEVICE_VENDOR_ID);
    bReturn = true;
  }
  else
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "<< %s (%X) -> broadcast (F): menu language '%s'", GetLogicalAddressName(), m_iLogicalAddress, lang);
    bReturn = m_handler->TransmitSetMenuLanguage(m_iLogicalAddress, lang, bIsReply);
  }
  MarkReady();
  return bReturn;
}
