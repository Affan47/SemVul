slotNewTrackProvider( Collections::TrackProvider *newTrackProvider )
{
    if( !newTrackProvider )
        return;

    if( newTrackProvider->possiblyContainsTrack( m_url ) )
    {
        Meta::TrackPtr track = newTrackProvider->trackForUrl( m_url );
        emit finishedLookup( track );
    }
}
