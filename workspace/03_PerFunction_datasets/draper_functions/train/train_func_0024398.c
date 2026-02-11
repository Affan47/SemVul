loadProgress(int progress)
{
    if (progress < 100 && progress > 0) {
        disconnect(m_stopReloadAction, SIGNAL(triggered()), m_viewReloadAction, SLOT(trigger()));
        m_stopReloadAction->setIcon(m_stopIcon);
        connect(m_stopReloadAction, SIGNAL(triggered()), m_viewStopAction, SLOT(trigger()));
        updateStopReloadActionText(true);
    } else {
        disconnect(m_stopReloadAction, SIGNAL(triggered()), m_viewStopAction, SLOT(trigger()));
        m_stopReloadAction->setIcon(m_reloadIcon);
        connect(m_stopReloadAction, SIGNAL(triggered()), m_viewReloadAction, SLOT(trigger()));
        updateStopReloadActionText(false);
    }
}
