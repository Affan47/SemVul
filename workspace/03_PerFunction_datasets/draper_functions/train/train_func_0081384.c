commitPlaylist( const CollectionScanner::Playlist &playlist )
{


    if( The::playlistManager() )
        The::playlistManager()->import( "file:"+playlist.path() );
}
