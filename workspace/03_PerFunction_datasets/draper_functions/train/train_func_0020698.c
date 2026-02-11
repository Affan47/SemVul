ProcessIdentifyTarget( const char *pszTarget,
                                   char **papszSiblingList,
                                   int bRecursive, int bReportFailures )

{
    GDALDriverH hDriver;
    VSIStatBufL sStatBuf;
    int i;

    hDriver = GDALIdentifyDriver( pszTarget, papszSiblingList );

    if( hDriver != NULL )
        printf( "%s: %s\n", pszTarget, GDALGetDriverShortName( hDriver ) );
    else if( bReportFailures )
        printf( "%s: unrecognised\n", pszTarget );

    if( !bRecursive || hDriver != NULL )
        return;

    if( VSIStatL( pszTarget, &sStatBuf ) != 0
        || !VSI_ISDIR( sStatBuf.st_mode ) )
        return;

    papszSiblingList = VSIReadDir( pszTarget );
    for( i = 0; papszSiblingList && papszSiblingList[i]; i++ )
    {
        if( EQUAL(papszSiblingList[i],"..")
            || EQUAL(papszSiblingList[i],".") )
            continue;

        CPLString osSubTarget =
            CPLFormFilename( pszTarget, papszSiblingList[i], NULL );

        ProcessIdentifyTarget( osSubTarget, papszSiblingList,
                               bRecursive, bReportFailures );
    }
    CSLDestroy(papszSiblingList);
}
