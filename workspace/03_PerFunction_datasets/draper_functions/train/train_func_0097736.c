undoStep()
{
    m_currentJob = 0;

    if (m_undoState == MAKINGDIRS)
        stepMakingDirectories();

    if (m_undoState == MOVINGFILES || m_undoState == STATINGFILE)
        stepMovingFiles();

    if (m_undoState == REMOVINGLINKS)
        stepRemovingLinks();

    if (m_undoState == REMOVINGDIRS)
        stepRemovingDirectories();

    if (m_currentJob) {
        if (m_uiInterface)
            m_currentJob->ui()->setWindow(m_uiInterface->parentWidget());
        QObject::connect(m_currentJob, SIGNAL(result(KJob*)),
                         this, SLOT(slotResult(KJob*)));
    }
}
