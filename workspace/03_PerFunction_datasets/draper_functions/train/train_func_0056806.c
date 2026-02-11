se_LoginWanted( nMessage & m )
{
#ifdef KRAWALL_SERVER


    ePlayerNetID * p;
    m >> p;

    if ( p && m.SenderID() == p->Owner() && !p->IsAuthenticated() )
    {

        m >> p->loginWanted;
        tString authName;


        m >> authName;
        p->SetRawAuthenticatedName( authName );


        if ( se_IsUserBanned( p, authName ) )
        {
            return;
        }

        se_RequestLogin( p );
    }
#else
    sn_ConsoleOut( tOutput( "$login_not_supported" ), m.SenderID() );
#endif
}
