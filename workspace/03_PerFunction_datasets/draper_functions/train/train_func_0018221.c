DoAnalyze( tCommandLineParser & parser )
    {

        tString forward;
        if ( parser.GetOption( forward, "--fastforward" ) )
        {

            s_fastForward = true;


            std::stringstream str(static_cast< char const * >( forward ) );
            str >> s_fastForwardTo;

            return true;
        }

        if ( parser.GetSwitch( "--benchmark" ) )
        {

            s_benchmark = true;
            return true;
        }

        return false;
    }
