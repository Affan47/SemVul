handshakeReturn( Request* req )
{
    Handshake* handshake = static_cast<Handshake*>( req );

    if ( handshake->failed() )
    {

        emit error( static_cast<RadioError>( handshake->resultCode() ),
                    handshake->errorMessage() );
        setState( State_Uninitialised );
        return;
    }

    if ( handshake->resultCode() == Request_Success )
    {
        m_session = handshake->session();
        m_basePath = handshake->basePath();

      #ifndef LINUX
        The::settings().setFingerprintUploadUrl( handshake->fingerprintUploadUrl() );
      #endif

        setState( State_Handshaken );

        if ( !m_pendingStation.isEmpty() )
        {
            playStation( m_pendingStation );
            m_pendingStation.clear();
        }
    }
    else
    {

        Q_ASSERT( handshake->resultCode() == Request_Aborted );
    }

}
