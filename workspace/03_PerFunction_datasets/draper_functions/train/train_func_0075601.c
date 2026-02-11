Identify( int nArgc, char **papszArgv )

{


    int bRecursive = FALSE, bReportFailures = FALSE;

    while( nArgc > 0 && papszArgv[0][0] == '-' )
    {
        if( EQUAL(papszArgv[0],"-r") )
            bRecursive = TRUE;
        else if( EQUAL(papszArgv[0],"-u") )
            bReportFailures = TRUE;
        else
            Usage();

        papszArgv++;
        nArgc--;
    }


    while( nArgc > 0 )
    {
        ProcessIdentifyTarget( papszArgv[0], NULL,
                               bRecursive, bReportFailures );
        nArgc--;
        papszArgv++;
    }
}
