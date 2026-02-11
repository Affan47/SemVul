matchAlbums( ServiceCollection *coll, const Meta::ArtistPtr &artist )
{
    if( !artist || !coll )
        return Meta::AlbumList();
    ArtistMap artistMap = coll->artistMap();
    if ( artist && artistMap.contains( artist->name() ) )
    {
        Meta::ArtistPtr artist2 = artistMap.value( artist->name() );

        Meta::AlbumList matchingAlbums;
        Meta::AlbumList albums = coll->albumMap().values();

        foreach( Meta::AlbumPtr albumPtr, albums ) {

            if ( albumPtr->albumArtist() == artist2 )
                matchingAlbums.push_back( albumPtr );
        }

        return matchingAlbums;
    }
    else
        return Meta::AlbumList();
}
