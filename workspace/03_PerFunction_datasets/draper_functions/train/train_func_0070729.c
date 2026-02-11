OnWrapMode(cb_unused wxCommandEvent& event)
{
    int i = GetPageIndexByWindow( GetPage(GetSelection()) );
    if (m_Pages.Item(i)->islogger && m_Pages.Item(i)->logger->HasFeature(Logger::Feature::IsWrappable))
    {
        TextCtrlLogger* tcl = static_cast<TextCtrlLogger*>(m_Pages.Item(i)->logger);
        if (tcl) tcl->ToggleWrapMode();
    }
}
