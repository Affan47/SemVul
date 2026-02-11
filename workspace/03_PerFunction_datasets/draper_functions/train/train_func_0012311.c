OnRelease(cb_unused bool appShutDown)
{
    if (m_StandAlone)
    {
        CodeBlocksDockEvent evt(cbEVT_REMOVE_DOCK_WINDOW);
        evt.pWindow = m_pListLog->GetWindow();
        Manager::Get()->ProcessEvent(evt);
        m_pListLog->DestroyControls(true);
        delete m_pListLog;
    }
    else
    {
        CodeBlocksLogEvent evt(cbEVT_REMOVE_LOG_WINDOW, m_pListLog);
        m_pListLog->DestroyControls(false);
        Manager::Get()->ProcessEvent(evt);
    }
    m_pListLog = nullptr;
}
