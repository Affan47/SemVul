GetChannelsCount() {
  int count = XVDR::Connection::GetChannelsCount();

  Lock();
  bool seen = m_emptyChannelsSeen;
  Unlock();

  if(!SupportChannelScan() || count > 0 || seen) {
    return count;
  }

  Lock();
  m_emptyChannelsSeen = true;
  Unlock();

  if(CGUIDialogYesNo::ShowAndGetInput(GUI, GetLocalizedString(30008).c_str(), GetLocalizedString(30075).c_str(), GetLocalizedString(30076).c_str())) {
    DialogChannelScan();
  }

  return count;
}
