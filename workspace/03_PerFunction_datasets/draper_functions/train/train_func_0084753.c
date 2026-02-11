runQuery()
{
    QSharedPointer<MemoryCollection> coll = m_collection.toStrongRef();
    if( coll )
        coll->acquireReadLock();

    if ( m_matchers )
    {
        Meta::TrackList result = coll ? m_matchers->match( coll.data() ) : Meta::TrackList();
        if ( m_filters )
        {
            Meta::TrackList filtered;
            foreach( Meta::TrackPtr track, result )
            {
                if( m_filters->filterMatches( track ) )
                    filtered.append( track );
            }
            handleResult( filtered );
        }
        else
            handleResult( result );
    }
    else if ( m_filters )
    {
        Meta::TrackList tracks = coll ? coll->trackMap().values() : Meta::TrackList();
        Meta::TrackList filtered;
        foreach( const Meta::TrackPtr &track, tracks )
        {
            if ( m_filters->filterMatches( track ) )
                filtered.append( track );
        }
        handleResult( filtered );
    }
    else
        handleResult();
    if( coll )
        coll->releaseLock();
}
