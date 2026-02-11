slotNewResultReady( Meta::TrackList list )
{
    foreach( Meta::TrackPtr track, list )
    {
        Meta::ArtistPtr artistPtr = track->artist();
        QString artist = artistPtr ? artistPtr->name() : QString();


        if( artist == m_currentArtistName )
            m_foundTracks.append( TrackPtr( new CollectionTrack( track ) ) );
    }
}
