DialogChannelScan() {
  if(!m_scanner->LoadSetup()) {
    CGUIDialogOk::Show(GUI, GetLocalizedString(30008).c_str(), NULL, GetLocalizedString(30074).c_str());
  }
  m_scanner->DoModal();
}
