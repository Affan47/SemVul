requestAbort()
{
    if ( m_qm ) {
        m_qm->abortQuery();
        m_qm->deleteLater();
        m_qm = 0;
    }
    m_abortRequested = true;
}
