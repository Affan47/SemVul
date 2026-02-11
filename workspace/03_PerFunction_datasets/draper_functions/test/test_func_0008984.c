tracksFromIndexes( const QModelIndexList &list ) const
{
    Meta::TrackList tracks;
    foreach( const QModelIndex &index, list )
    {
        if( IS_TRACK(index) )
            tracks << trackFromIndex( index );
        else if( Playlists::PlaylistPtr playlist = playlistFromIndex( index ) )
        {
            playlist->makeLoadingSync();

            playlist->triggerTrackLoad();
            tracks << playlist->tracks();
        }
    }
    return tracks;
}
