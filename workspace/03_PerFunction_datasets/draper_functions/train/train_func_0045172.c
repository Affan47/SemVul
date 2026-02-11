sn_KickUser(int i, const tOutput& reason, REAL severity, nServerInfoBase * redirectTo )
{

    con << tOutput( "$network_kill_log", i, reason );


    if ( severity > 0 )
    {
        nMachine::GetMachine(i).OnKick( severity );
    }


    sn_DisconnectUser( i, reason, redirectTo );
}
