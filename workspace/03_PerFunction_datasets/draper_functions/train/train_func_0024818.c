CPLLockFile( const char *pszPath, double dfWaitInSeconds )

{
    FILE      *fpLock;
    char      *pszLockFilename;


    pszLockFilename = (char *) CPLMalloc(strlen(pszPath) + 30);
    sprintf( pszLockFilename, "%s.lock", pszPath );

    fpLock = fopen( pszLockFilename, "r" );
    while( fpLock != NULL && dfWaitInSeconds > 0.0 )
    {
        fclose( fpLock );
        CPLSleep( MIN(dfWaitInSeconds,0.5) );
        dfWaitInSeconds -= 0.5;

        fpLock = fopen( pszLockFilename, "r" );
    }

    if( fpLock != NULL )
    {
        fclose( fpLock );
        CPLFree( pszLockFilename );
        return NULL;
    }

    fpLock = fopen( pszLockFilename, "w" );

    if( fpLock == NULL )
    {
        CPLFree( pszLockFilename );
        return NULL;
    }

    fwrite( "held\n", 1, 5, fpLock );
    fclose( fpLock );

    return pszLockFilename;
}
