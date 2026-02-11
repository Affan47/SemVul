getRenderer( const QString& name )
{
    QReadLocker readLocker( &m_lock );
    if( ! m_renderers[name] )
    {
        readLocker.unlock();
        if( !loadSvg( name ) )
        {
            QWriteLocker writeLocker( &m_lock );
            m_renderers[name] = new QSvgRenderer();
        }
        readLocker.relock();
    }
    return m_renderers[name];
}
