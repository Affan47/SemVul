matchingTracks( const Meta::TrackList& playlist,
                                  int contextCount, int finalCount,
                                  Dynamic::TrackCollectionPtr universe ) const
{
    DEBUG_BLOCK;
debug() << "universe:" << universe.data();

    m_tracks = Dynamic::TrackSet( universe, true );
    m_outstandingMatches = 0;

    foreach( Dynamic::BiasPtr bias, m_biases )
    {
        Dynamic::TrackSet tracks = bias->matchingTracks( playlist, contextCount, finalCount, universe );
        if( tracks.isOutstanding() )
            m_outstandingMatches++;
        else
            m_tracks.intersect( tracks );


        if( m_tracks.isEmpty() )
            break;
    }


    if( m_outstandingMatches > 0 )
        return Dynamic::TrackSet();
    else
        return m_tracks;
}
