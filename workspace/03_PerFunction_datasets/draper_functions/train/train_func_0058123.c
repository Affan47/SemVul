requestPlaylistChunk()
{
    Q_ASSERT( !m_session.isEmpty() );

    LOGL( 4, "Requesting playlist chunk..." );

    m_currentRequest = new GetXspfPlaylistRequest( m_session, m_basePath,
        The::settings().version(), The::currentUser().isDiscovery() );
    connect( m_currentRequest,  SIGNAL( result( Request* ) ),
             this,              SLOT  ( xspfPlaylistRequestReturn( Request* ) ) );
    m_currentRequest->start();

    m_requestingPlaylist = true;
}
