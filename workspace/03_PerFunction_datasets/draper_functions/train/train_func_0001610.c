slotToggleProviderButton()
{
    QString filter;
    QActionList checkedActions;
    foreach( const Playlists::PlaylistProvider *p, m_providerActions.keys() )
    {
        QAction *action = m_providerActions.value( p );
        if( action->isChecked() )
        {
            QString escapedName = QRegExp::escape( p->prettyName() ).replace( " ", "\\ " );
            filter += QString( filter.isEmpty() ? "%1" : "|%1" ).arg( escapedName );
            checkedActions << action;
            action->setEnabled( true );
        }
    }

    if( checkedActions.count() == m_providerActions.count() )
        filter = QString();

    m_filterProxy->setFilterRegExp( filter );


    if( checkedActions.count() == 1 )
        checkedActions.first()->setEnabled( false );
}
