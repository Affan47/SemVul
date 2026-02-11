formats() const
{
    QStringList formats( QMimeData::formats() );
    if( !d->tracks.isEmpty() || !d->queryMakers.isEmpty() || !d->playlistGroups.isEmpty() || !d->bookmarks.isEmpty() || !d->bookmarkGroups.isEmpty() )
    {
        formats.append( TRACK_MIME );
        formats.append( PLAYLIST_MIME );
        formats.append( PLAYLISTBROWSERGROUP_MIME );
        formats.append( PODCASTCHANNEL_MIME );
        formats.append( PODCASTEPISODE_MIME );
        formats.append( BOOKMARKGROUP_MIME );
        formats.append( AMAROKURL_MIME );

        if( !formats.contains( "text/uri-list" ) )
            formats.append( "text/uri-list" );
        if( !formats.contains( "text/plain" ) )
            formats.append( "text/plain" );
    }

    return formats;
}
