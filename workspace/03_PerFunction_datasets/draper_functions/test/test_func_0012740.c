insertIntoPlaylist( Playlist::AddOptions options )
{
    Meta::TrackList tracks;


    foreach( Playlists::PlaylistPtr playlist, m_actionPlaylists )
    {
        tracks << playlist->tracks();
    }


    foreach( Playlists::PlaylistPtr playlist, m_actionTracks.uniqueKeys() )
    {
        if( m_actionPlaylists.contains( playlist ) )
            continue;

        Meta::TrackList playlistTracks = playlist->tracks();
        QList<int> positions = m_actionTracks.values( playlist );
        qSort( positions );
        foreach( int position, positions )
        {
            if( position >= 0 && position < playlistTracks.count() )
                tracks << playlistTracks.at( position );
        }
    }

    if( !tracks.isEmpty() )
        The::playlistController()->insertOptioned( tracks, options );
}
