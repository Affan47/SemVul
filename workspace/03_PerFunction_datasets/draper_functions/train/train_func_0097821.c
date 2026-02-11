findTitle( const QString& id, const QString& defaultTitle  )
{
    for ( int i = m_clients.count() - 1; i >= 0; i-- ) {
        QString title = m_clients.at( i )->title( id );
        if ( !title.isEmpty() )
            return title;
    }

    return defaultTitle;
}
