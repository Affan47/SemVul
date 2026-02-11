DisplayEventLog(bool bShowWindow) {
    if (m_pEventLog) {
        if (bShowWindow) {
            if (m_pEventLog->IsIconized()) {
                m_pEventLog->Iconize(false);
            }
            m_pEventLog->Raise();
        }
    } else {
        m_pEventLog = new CDlgEventLog();
        if (m_pEventLog) {
            m_pEventLog->Show(bShowWindow);
            if (bShowWindow) {
                m_pEventLog->Raise();
            }
            if (m_pFrame) {
                m_pFrame->UpdateRefreshTimerInterval();
            }
        }
    }
}
