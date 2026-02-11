closeDocument()
{
    if (!m_doc) {
        return;
    }

    Q_FOREACH(DocumentObserver *obs, m_observers) {
        obs->documentClosed();
    }

    m_currentPage = 0;
    delete m_doc;
    m_doc = 0;

    m_fileSaveCopyAct->setEnabled(false);
}
