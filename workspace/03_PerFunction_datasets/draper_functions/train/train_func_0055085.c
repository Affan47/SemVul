removePlaylist( Playlists::PlaylistPtr playlist, int category )
{
    if( typeid( *playlist.data() ) == typeid( SyncedPlaylist ) )
    {
        SyncedPlaylistPtr syncedPlaylist = SyncedPlaylistPtr::dynamicCast( playlist );


        syncedPlaylist->removePlaylistsFrom( playlist->provider() );
        if( syncedPlaylist->isEmpty() )
            m_playlistMap.remove( category, playlist );

        m_syncNeeded.removeAll( syncedPlaylist );
    }
    else
    {
        m_playlistMap.remove( category, playlist );
    }

    emit playlistRemoved( playlist, category );
}
