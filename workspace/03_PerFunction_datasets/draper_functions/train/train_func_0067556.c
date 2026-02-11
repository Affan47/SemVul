slotFilterChanged( const QString & filter )
{
    DEBUG_BLOCK


    if ( filter == m_lastFilter )
        return;

    debug() << "New filter: " << filter;

    m_lastFilter = filter;

    if( filter.isEmpty() )
    {
        m_nextAction->setEnabled( false );
        m_previousAction->setEnabled( false );

        QPalette p = m_searchEdit->palette();
        p.setColor( QPalette::Base, palette().color( QPalette::Base ) );
        m_searchEdit->setPalette( p );

        emit( filterCleared() );

        return;
    }

    emit( filterChanged( filter, m_searchFieldsMask, m_showOnlyMatches ) );
}
