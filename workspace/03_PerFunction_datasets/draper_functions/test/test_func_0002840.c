queueQueryForAlbum( Meta::AlbumPtr album )
{
    QString query( album->name() );
    if( album->hasAlbumArtist() )
        query += ' ' + album->albumArtist()->name();
    queueQuery( album, query, 0 );
}
