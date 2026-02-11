execute( vector < string > & argv,
                                                string & out )
{
    string hostname;
    t_CKINT port;
    t_CKINT result = 0;


    if( argv.size() == 0 )

    {
        argv.push_back( "localhost:8888" );
        hostname = "localhost";
        port = 8888;
    }

    else
    {
        string::size_type i = argv[0].find( ":" );

        if( i == string::npos )

        {
            hostname = argv[0];
            port = 8888;
            argv[0] += ":8888";
        }

        else
        {
            port = strtol( argv[0].c_str() + i + 1, NULL, 10 );
            if( port == 0 )
                out += string( "error: invalid port '" ) +
                       string( argv[0].c_str() + i + 1 ) + "'\n";

            else
                hostname = string( argv[0], 0, i );
        }
    }

    if( port != 0 )
    {


        Chuck_Shell_Network_VM * new_vm = new Chuck_Shell_Network_VM();
        new_vm->init( hostname, port );


        SAFE_DELETE( caller->current_vm );
        caller->current_vm = new_vm;
        out += argv[0] + " is now current VM\n";
        result = 0;
    }

    else
    {
        out += "error: unable to attach to " + argv[0] + "\n";
        result = -1;
    }

    if( argv.size() > 1 )
        out += "warning: ignoring excess arguments...\n";

    return result;
}
