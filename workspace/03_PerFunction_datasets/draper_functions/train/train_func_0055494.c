reorderRows( const QList<int> &from, const QList<int> &to )
{
    DEBUG_BLOCK
    if( from.size() != to.size() )
        return;


    {
        QSet<int> fromItems( from.toSet() );
        QSet<int> toItems( to.toSet() );

        if( fromItems.size() != from.size() || toItems.size() != to.size() || fromItems != toItems )
        {
            error() << "row move lists malformed:";
            error() << from;
            error() << to;
            return;
        }
    }

    MoveCmdList bottomModelCmds;
    for( int i = 0; i < from.size(); i++ )
    {
        debug() << "moving rows:" << from.at( i ) << "->" << to.at( i );
        if( ( from.at( i ) >= 0 ) && ( from.at( i ) < m_topModel->qaim()->rowCount() ) )
            if( from.at( i ) != to.at( i ) )
                bottomModelCmds.append( MoveCmd( m_topModel->rowToBottomModel( from.at( i ) ), m_topModel->rowToBottomModel( to.at( i ) ) ) );
    }

    if( bottomModelCmds.size() > 0 )
        m_undoStack->push( new MoveTracksCmd( 0, bottomModelCmds ) );

    emit changed();
}
