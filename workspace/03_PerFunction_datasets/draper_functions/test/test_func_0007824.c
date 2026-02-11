expand( int onlyWithTupleFlags )
{
    if( onlyWithTupleFlags < 0 )
    {
        QAction *action = qobject_cast<QAction *>( sender() );
        if( action )
            onlyWithTupleFlags = action->data().toInt();
        else
            onlyWithTupleFlags = 0;
    }

    for( int i = 0; i < m_matchedProxyModel->rowCount(); i++ )
    {
        QModelIndex idx = m_matchedProxyModel->index( i, 0 );
        if( matchedTreeView->isExpanded( idx ) )
            continue;

        int flags = idx.data( MatchedTracksModel::TupleFlagsRole ).toInt();
        if( ( flags & onlyWithTupleFlags ) == onlyWithTupleFlags )
            matchedTreeView->expand( idx );
    }
}
