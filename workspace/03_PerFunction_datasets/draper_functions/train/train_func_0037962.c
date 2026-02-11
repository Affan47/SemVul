changeStationRequestReturn( Request* req )
{
    if ( req == m_currentChangeRequest )
    {
        m_currentChangeRequest = 0;
    }

    if ( req->aborted() )
    {
        return;
    }

    ChangeStationRequest* request = static_cast<ChangeStationRequest*>( req );

    if ( request->failed() )
    {
        if ( request->resultCode() == ChangeStation_InvalidSession )
        {
            reHandshake();
        }
        else {
             if (request->resultCode() == ChangeStation_FreeTrialExpired)
                 emit error( Radio_FreeTrialExpired, request->errorMessage() );
             else

                 emit error( static_cast<RadioError>( request->resultCode() ),
                             request->errorMessage() );


            setState( State_Stopping );
            setState( State_Stopped );


            m_resumePossible = false;
        }

        return;
    }

    LOGL( 3, "Adjust succeeded, now fetch playlist" );


    m_stationName = request->stationName();

    if ( !request->stationName().isEmpty() )
    {


        addStationToHistory( m_stationUrl, m_stationName );
    }


    if ( request->hasXspf() )
    {


        setState( State_FetchingPlaylist );
        m_playlist.setXspf( request->xspf() );
    }
    else
    {

        The::currentUser().setResumeStation( m_stationUrl );

        m_playlist.setBasePath( m_basePath );
        m_playlist.setSession( m_session );
        setState( State_FetchingPlaylist );
    }
}
