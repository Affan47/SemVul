se_MoveToConf(std::istream &s, REAL severity, const char * command )
{
    if ( se_NeedsServer( "KICK/MOVE_TO", s ) )
    {
        return;
    }


    int num = se_ReadUser( s );


    tString server = se_defaultKickToServer;
    if ( !s.eof() )
    {
        s >> server;
    }

    int pos, port = se_defaultKickToPort;
    if ( ( pos = server.StrPos( ":" ) ) != -1 )
    {
        port = atoi( server.SubStr( pos + 1 ) );
        server = server.SubStr( 0, pos );
    }

    nServerInfoRedirect redirect( server, port );

    tString reason = se_defaultKickToReason;
    if ( !s.eof() )
        reason.ReadLine(s);


    if ( num > 0 && !s.good() )
    {
        sn_KickUser( num ,  reason.Len() > 1 ? static_cast< char const *>( reason ) : "$network_kill_kick", severity, &redirect );
    }
    else
    {
        con << tOutput( "$kickmove_usage", command );
        return;
    }
}
