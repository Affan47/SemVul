metadataChanged( Meta::AlbumPtr album )
{
    if( !m_currentTrack || !m_currentTrack->album() )
        return;


    if( album == m_currentTrack->album() )
        updateCover();


}
