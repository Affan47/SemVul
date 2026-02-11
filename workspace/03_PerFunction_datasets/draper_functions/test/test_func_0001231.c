DeleteDataSource( const char *pszDataSource )

{
    int iExt;
    VSIStatBufL sStatBuf;
    static const char *apszExtensions[] =
        { "shp", "shx", "dbf", "sbn", "sbx", "prj", "idm", "ind",
          "qix", "cpg", NULL };

    if( VSIStatL( pszDataSource, &sStatBuf ) != 0 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "%s does not appear to be a file or directory.",
                  pszDataSource );

        return OGRERR_FAILURE;
    }

    if( VSI_ISREG(sStatBuf.st_mode)
        && (EQUAL(CPLGetExtension(pszDataSource),"shp")
            || EQUAL(CPLGetExtension(pszDataSource),"shx")
            || EQUAL(CPLGetExtension(pszDataSource),"dbf")) )
    {
        for( iExt=0; apszExtensions[iExt] != NULL; iExt++ )
        {
            const char *pszFile = CPLResetExtension(pszDataSource,
                                                    apszExtensions[iExt] );
            if( VSIStatL( pszFile, &sStatBuf ) == 0 )
                VSIUnlink( pszFile );
        }
    }
    else if( VSI_ISDIR(sStatBuf.st_mode) )
    {
        char **papszDirEntries = CPLReadDir( pszDataSource );
        int  iFile;

        for( iFile = 0;
             papszDirEntries != NULL && papszDirEntries[iFile] != NULL;
             iFile++ )
        {
            if( CSLFindString( (char **) apszExtensions,
                               CPLGetExtension(papszDirEntries[iFile])) != -1)
            {
                VSIUnlink( CPLFormFilename( pszDataSource,
                                            papszDirEntries[iFile],
                                            NULL ) );
            }
        }

        CSLDestroy( papszDirEntries );

        VSIRmdir( pszDataSource );
    }

    return OGRERR_NONE;
}
