matchingTracks( const Meta::TrackList& playlist,
                                          int contextCount, int finalCount,
                                          Dynamic::TrackCollectionPtr universe ) const
{
    Q_UNUSED( playlist );
    Q_UNUSED( contextCount );
    Q_UNUSED( finalCount );

    if( tracksValid() )
        return m_tracks;

    m_tracks = Dynamic::TrackSet( universe, m_invert );

    QTimer::singleShot(0,
                       const_cast<SimpleMatchBias*>(this),
                       SLOT(newQuery()));

    return Dynamic::TrackSet();
}
