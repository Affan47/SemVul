OnCtrlAltTab(cb_unused wxCommandEvent& event)
{
    wxCommandEvent dummy;
    switch (m_LastCtrlAltTabWindow)
    {
      case 1:
        m_LastCtrlAltTabWindow = 2;
        OnFocusEditor(dummy);
        break;
      case 2:
        m_LastCtrlAltTabWindow = 3;
        OnFocusLogsAndOthers(dummy);
        break;
      case 3:
      default:
        m_LastCtrlAltTabWindow = 1;
        OnFocusManagement(dummy);
    }
}
