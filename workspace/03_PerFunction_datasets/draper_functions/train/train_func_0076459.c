updaterFinished( const QString &scriptPath )
{
    DEBUG_BLOCK

    m_updateSemaphore.release();
    loadScript( scriptPath );
    if ( m_updateSemaphore.tryAcquire(m_nScripts) )
    {
        configChanged( true );
    }
    sender()->deleteLater();
}
