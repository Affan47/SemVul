addTrack( ScriptableServiceTrack * track )
{
    int artistId = -1;
    int genreId = -1;

    TrackPtr trackPtr = TrackPtr( track );
    m_collection->acquireWriteLock();
    m_collection->addTrack( trackPtr );
    m_collection->releaseLock();

    m_trackIdCounter++;
    track->setId( m_trackIdCounter );


    int albumId = track->albumId();


    if ( m_levels > 1 ) {

        if ( !m_ssAlbumIdMap.contains( albumId ) ){
            delete track;
            return -1;
        }

        ScriptableServiceAlbum * album = m_ssAlbumIdMap.value( albumId );

        track->setAlbum( album->prettyName() );
        track->setAlbumPtr( AlbumPtr( album ) );
        album->addTrack( trackPtr );

        artistId = album->artistId();

     }

     if ( m_levels > 2 ) {

         if ( !m_ssArtistIdMap.contains( artistId ) ) {
             delete track;
             return -1;
         }

         ScriptableServiceArtist * artist = m_ssArtistIdMap.value( artistId );
         track->setArtist( artist->prettyName() );
         track->setArtist( ArtistPtr( artist ) );
         artist->addTrack( trackPtr );

         genreId = artist->genreId();
     }

     if ( m_levels == 4) {

         if ( !m_ssGenreIdMap.contains( genreId ) ) {
             delete track;
             return -1;
         }

         ScriptableServiceGenre * genre = m_ssGenreIdMap.value( genreId );
         track->setGenre( genre->prettyName() );
         track->setGenre( GenrePtr( genre ) );
         genre->addTrack( trackPtr );

     }

    m_ssTrackIdMap.insert( m_trackIdCounter, track );
    m_collection->acquireWriteLock();
    m_collection->addTrack( trackPtr );
    m_collection->releaseLock();


    return m_trackIdCounter;
}
