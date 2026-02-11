fetchMetaData()
{
    if ( m_currentTrack.isEmpty() || !m_user->settings().isMetaDataEnabled() )
        return;

    m_activeArtistReq = new ArtistMetaDataRequest();
    m_activeTrackReq = new TrackMetaDataRequest();

    m_activeArtistReq->setArtist( m_currentTrack.artist() );
    m_activeArtistReq->setParent( this );
    m_activeArtistReq->setLanguage( The::settings().appLanguage() );
    m_activeArtistReq->start();

    m_activeTrackReq->setTrack( m_currentTrack );
    m_activeTrackReq->setParent( this );
    m_activeTrackReq->setLanguage( The::settings().appLanguage() );
    m_activeTrackReq->start();
}
