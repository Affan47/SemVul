deleteTables()
{
    DEBUG_BLOCK

    SqlStorage *sqlStorage = CollectionManager::instance()->sqlStorage();

    if( !sqlStorage )
    {
        debug() << "No SQL Storage available!";
        return;
    }

    sqlStorage->query( "DROP INDEX parent_podchannel ON playlist_groups;" );
    sqlStorage->query( "DROP INDEX parent_playlist ON playlists;" );
    sqlStorage->query( "DROP INDEX parent_playlist_tracks ON playlist_tracks;" );
    sqlStorage->query( "DROP INDEX playlist_tracks_uniqueid ON playlist_tracks;" );

    sqlStorage->query( "DROP TABLE IF EXISTS playlist_groups;" );
    sqlStorage->query( "DROP TABLE IF EXISTS playlists;" );
    sqlStorage->query( "DROP TABLE IF EXISTS playlist_tracks;" );

}
