readArgs()
{
    QStringList argslist = arguments();
    if( argslist.size() < 2 )
        displayHelp();
    bool nomore = false;
    int argnum = 0;
    foreach( const QString &arg, argslist )
    {
        ++argnum;
        if( arg.isEmpty() || argnum == 1 )
            continue;
        if( nomore )
        {
            m_fileFolderList.append( arg );
        }
        else if( arg.startsWith( "--" ) )
        {
            QString myarg = QString( arg ).remove( 0, 2 );
            if ( myarg == "recurse" || myarg == "recursively" )
                m_recurse = true;
            else if( myarg == "verbose" )
                m_verbose = true;
            else if( myarg == "quiet" )
                m_quiet = true;
            else if( myarg == "newid" )
                m_newid = true;
            else if( myarg == "delete" )
                m_delete = true;
            else
                displayHelp();
        }
        else if( arg.startsWith( '-' ) )
        {
            QString myarg = QString( arg ).remove( 0, 1 );
            int pos = 0;
            while( pos < myarg.length() )
            {
                if( myarg[pos] == 'd' )
                    m_delete = true;
                else if( myarg[pos] == 'n' )
                    m_newid = true;
                else if( myarg[pos] == 'q' )
                    m_quiet = true;
                else if( myarg[pos] == 'r' )
                    m_recurse = true;
                else if( myarg[pos] == 'v' )
                    m_verbose = true;
                else
                    displayHelp();

                ++pos;
            }
        }
        else
        {
            nomore = true;
            m_fileFolderList.append( arg );
        }
    }
}
