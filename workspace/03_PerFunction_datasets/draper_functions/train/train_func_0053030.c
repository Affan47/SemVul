headerReceived( const QHttpResponseHeader&  )
{
    if ( responseHeaderCode() == 401 )
    {
        setFailed( Playlist_InvalidSession,
            tr( "Invalid session. Please re-handshake." ) );
    }
    else if ( responseHeaderCode() == 403 )
    {
        setFailed( Playlist_FreeTrialExpired, "" );
    }
    else if ( responseHeaderCode() == 503 )
    {
        setFailed( Playlist_RecSysDown,
            tr( "Sorry, the playlist service is not responding.\n"
                "Please try again later." ) );
    }

    return true;
}
