OnAttach()
{


    if(LogManager* LogMan = Manager::Get()->GetLogManager())
    {
        m_CcccLog = new TextCtrlLogger();
        m_LogPageIndex = LogMan->SetLog(m_CcccLog);
        LogMan->Slot(m_LogPageIndex).title = _("Cccc");
        CodeBlocksLogEvent evtAdd1(cbEVT_ADD_LOG_WINDOW, m_CcccLog, LogMan->Slot(m_LogPageIndex).title);
        Manager::Get()->ProcessEvent(evtAdd1);
    }
}
