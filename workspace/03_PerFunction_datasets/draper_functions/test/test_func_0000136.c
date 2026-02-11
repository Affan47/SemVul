OnViewList(wxCommandEvent& event)
{
    if (m_StandAlone)
    {
        CodeBlocksDockEvent evt(event.IsChecked() ? cbEVT_SHOW_DOCK_WINDOW : cbEVT_HIDE_DOCK_WINDOW);
        evt.pWindow = m_pListLog->GetWindow();
        Manager::Get()->ProcessEvent(evt);
    }
    else
    {
        if (event.IsChecked())
        {
            CodeBlocksLogEvent evtShow(cbEVT_SHOW_LOG_MANAGER);
            Manager::Get()->ProcessEvent(evtShow);
            CodeBlocksLogEvent evt(cbEVT_SWITCH_TO_LOG_WINDOW, m_pListLog);
            Manager::Get()->ProcessEvent(evt);
        }
        else
        {
            CodeBlocksLogEvent evt(cbEVT_HIDE_LOG_WINDOW, m_pListLog);
            Manager::Get()->ProcessEvent(evt);
        }
    }
}
