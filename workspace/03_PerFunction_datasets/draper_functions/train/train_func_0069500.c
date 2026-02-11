findAction( const QString& id )
{
    for ( int i = m_clients.count() - 1; i >= 0; i-- ) {
        QAction* action = m_clients.at( i )->action( id );
        if ( action )
            return action;
    }

    return NULL;
}
