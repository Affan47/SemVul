match( const TrackList &tracks )
{
    if( !m_year )
        return TrackList();
    TrackList matchingTracks;
    int year = m_year->year();
    foreach( TrackPtr track, tracks )
        if ( track->year()->year() == year )
            matchingTracks.append( track );
    if ( isLast() || matchingTracks.count() == 0)
        return matchingTracks;
    else
        return next()->match( matchingTracks );
}
