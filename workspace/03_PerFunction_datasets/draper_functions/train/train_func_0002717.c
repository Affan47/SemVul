AIGReadBounds( const char * pszCoverName, AIGInfo_t * psInfo )

{
    char	*pszHDRFilename;
    VSILFILE	*fp;
    double	adfBound[4];


    pszHDRFilename = (char *) CPLMalloc(strlen(pszCoverName)+40);
    sprintf( pszHDRFilename, "%s/dblbnd.adf", pszCoverName );

    fp = AIGLLOpen( pszHDRFilename, "rb" );

    if( fp == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Failed to open grid bounds file:\n%s\n",
                  pszHDRFilename );

        CPLFree( pszHDRFilename );
        return( CE_Failure );
    }

    CPLFree( pszHDRFilename );


    VSIFReadL( adfBound, 1, 32, fp );

    VSIFCloseL( fp );

#ifdef CPL_LSB
    CPL_SWAPDOUBLE(adfBound+0);
    CPL_SWAPDOUBLE(adfBound+1);
    CPL_SWAPDOUBLE(adfBound+2);
    CPL_SWAPDOUBLE(adfBound+3);
#endif

    psInfo->dfLLX = adfBound[0];
    psInfo->dfLLY = adfBound[1];
    psInfo->dfURX = adfBound[2];
    psInfo->dfURY = adfBound[3];

    return( CE_None );
}
