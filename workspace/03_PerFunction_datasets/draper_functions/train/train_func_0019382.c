setupSync( const Playlists::PlaylistPtr master, const Playlists::PlaylistPtr slave )
{
    DEBUG_BLOCK
    debug() << "master: " << master->uidUrl();
    debug() << "slave: " << slave->uidUrl();


    if( hasToSync( master, slave ) )
       return;

    Playlists::PlaylistPtr tempMaster;
    Playlists::PlaylistPtr tempSlave;

    m_syncRelStore->addSync( master, slave );

    foreach( const Playlists::PlaylistPtr tempPlaylist, m_playlistMap )
    {
        if( master == tempPlaylist )
        {
            tempMaster = tempPlaylist;
            break;
        }
    }

    foreach( const Playlists::PlaylistPtr tempPlaylist, m_playlistMap )
    {
        if( slave == tempPlaylist )
        {
            tempSlave = tempPlaylist;
            break;
        }
    }

    if( tempMaster && tempSlave )
    {
        SyncedPlaylistPtr syncedPlaylist = m_syncRelStore->asSyncedPlaylist( tempMaster );

        m_syncRelStore->asSyncedPlaylist( tempSlave );

        Playlists::PlaylistPtr syncedPlaylistPtr =
                        Playlists::PlaylistPtr::dynamicCast( syncedPlaylist );

        int category = syncedPlaylist->master()->provider()->category();

        if( !m_playlistMap.values( category ).contains( syncedPlaylistPtr ) )
        {
            removePlaylist( tempMaster, tempMaster->provider()->category() );
            removePlaylist( tempSlave, tempSlave->provider()->category() );

            m_syncedPlaylistMap.insert( syncedPlaylist, tempMaster );
            m_syncedPlaylistMap.insert( syncedPlaylist, tempSlave );

            m_playlistMap.insert( category, syncedPlaylistPtr );

            emit playlistAdded( syncedPlaylistPtr, category );
        }
    }
}
