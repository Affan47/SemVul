GetMasters()
{

    double time = tSysTimeFloat();
    static double deleteTime = time + 60.0;
    if ( time > deleteTime )
    {
        deleteTime = time + 60.0;

        while (sn_masterList)
            delete sn_masterList;
    }

    if (!sn_masterList)
    {

        nServerInfo * oldFirstServer = sn_FirstServer;
        sn_FirstServer = NULL;


        Load( tDirectories::Config(), "master.srv" );


        while ( sn_FirstServer )
        {
            nServerInfo * server = sn_FirstServer;
            server->Remove();
            server->Insert( sn_masterList );
        }


        sn_FirstServer = oldFirstServer;
    }

    return sn_masterList;
}
