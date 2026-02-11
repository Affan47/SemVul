removePlaylistsFrom( Playlists::PlaylistProvider *provider )
{
    foreach( Playlists::PlaylistPtr playlist, m_playlists )
    {
        if( playlist->provider() == provider )
        {
            unsubscribeFrom( playlist );
            m_playlists.removeAll( playlist );
        }
    }
}
