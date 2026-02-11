trackMatches( int position,
                                      const Meta::TrackList& playlist,
                                      int contextCount ) const
{
    Q_UNUSED( contextCount );

    if( position <= 0 || playlist.count() <= position )
        return true;

    Meta::TrackPtr track = playlist[position-1];
    Meta::AlbumPtr album = track->album();
    Meta::TrackPtr currentTrack = playlist[position];
    Meta::AlbumPtr currentAlbum = currentTrack->album();

    if( !album || album->tracks().isEmpty() )
        return false;

    Meta::TrackList albumTracks = album->tracks();
    if( sameTrack( track, albumTracks.last() ) && m_follow != DontCare )
        return false;


    if( m_follow == DirectlyFollow )
    {
        for( int i = 1; i < albumTracks.count(); i++ )
            if( sameTrack( albumTracks[i-1], track ) )
                return sameTrack( albumTracks[i], currentTrack );
        return false;
    }
    else if( m_follow == Follow )
    {
        bool found = false;
        for( int i = 0; i < albumTracks.count(); i++ )
        {
            if( found && sameTrack( albumTracks[i], currentTrack ) )
                return true;
            if( sameTrack( albumTracks[i], track ) )
                found = true;
        }
        return false;
    }
    else if( m_follow == DontCare )
    {
        return album == currentAlbum;
    }
    return false;
}
