slotTriggered()
{


    if( m_albums.size() == 1 )
        CoverFetcher::instance()->manualFetch( m_albums.first() );
    else
        CoverFetcher::instance()->queueAlbums( m_albums );
}
