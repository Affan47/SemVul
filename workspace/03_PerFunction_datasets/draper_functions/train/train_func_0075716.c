addPlaylist( Playlists::PlaylistPtr playlist, int category )
{
    SyncedPlaylistPtr syncedPlaylist = m_syncRelStore->asSyncedPlaylist( playlist );


    if( syncedPlaylist )
    {
        if( !m_syncedPlaylistMap.keys().contains( syncedPlaylist ) )
        {


            foreach( Playlists::PlaylistPtr existingPlaylist, m_playlistMap.values( category ) )
            {

                if( m_syncRelStore->asSyncedPlaylist( existingPlaylist ) == syncedPlaylist )
                {
                    m_playlistMap.remove( category, existingPlaylist );

                    if( !m_syncedPlaylistMap.values( syncedPlaylist ).contains( existingPlaylist ) )
                        m_syncedPlaylistMap.insert( syncedPlaylist, existingPlaylist );
                }
            }
        }

        if( !m_syncedPlaylistMap.values( syncedPlaylist ).contains( playlist ) )
        {
            m_syncedPlaylistMap.insert( syncedPlaylist, playlist );


            m_syncNeeded.append( syncedPlaylist );
            QTimer::singleShot( 0, this, SLOT(slotSyncNeeded()) );
        }


        playlist = PlaylistPtr::dynamicCast( syncedPlaylist );

        if( m_playlistMap.values( category ).contains( playlist ) )
        {

             emit playlistUpdated( playlist, category );
             return;
        }
    }

    m_playlistMap.insert( category, playlist );

    emit playlistAdded( playlist, category );
}
