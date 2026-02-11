engineDescriptionDownloadDone()
{

    bool __emit = true;
    for(int i = 0; i < m_WorkingEngines.count(); ++i) {
        IServerEngine *engine = m_WorkingEngines.at(i);
        if (engine->downloadQueueCount() > 0) {

            __emit = false;
        } else {
            disconnect(engine, SIGNAL(queueDowloaded()), this, SLOT(engineDescriptionDownloadDone()));
        }
    }
    if (m_ProgressBar)
        m_ProgressBar->setValue(m_ProgressBar->value() + 1);
    if (__emit) {
        Q_EMIT allServerDescriptionAvailable();
        m_ProgressBar = 0;
    }
}
