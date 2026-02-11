OpenDir( GDALOpenInfo * poOpenInfo )

{
    int bAllowRGBAInterface = TRUE;
    const char* pszFilename = poOpenInfo->pszFilename;
    if( EQUALN(pszFilename,"GTIFF_RAW:", strlen("GTIFF_RAW:")) )
    {
        bAllowRGBAInterface = FALSE;
        pszFilename += strlen("GTIFF_RAW:");
    }

    if( !EQUALN(pszFilename,"GTIFF_DIR:",strlen("GTIFF_DIR:")) )
        return NULL;


    pszFilename += strlen("GTIFF_DIR:");
    int        bAbsolute = FALSE;
    toff_t     nOffset;

    if( EQUALN(pszFilename,"off:",4) )
    {
        bAbsolute = TRUE;
        pszFilename += 4;
    }

    nOffset = atol(pszFilename);
    pszFilename += 1;

    while( *pszFilename != '\0' && pszFilename[-1] != ':' )
        pszFilename++;

    if( *pszFilename == '\0' || nOffset == 0 )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Unable to extract offset or filename, should take the form\n"
                  "GTIFF_DIR:<dir>:filename or GTIFF_DIR:off:<dir_offset>:filename" );
        return NULL;
    }


    TIFF	*hTIFF;

    if (!GTiffOneTimeInit())
        return NULL;

    hTIFF = VSI_TIFFOpen( pszFilename, "r" );
    if( hTIFF == NULL )
        return( NULL );


    if( !bAbsolute )
    {
        while( nOffset > 1 )
        {
            if( TIFFReadDirectory( hTIFF ) == 0 )
            {
                XTIFFClose( hTIFF );
                CPLError( CE_Failure, CPLE_OpenFailed,
                          "Requested directory %lu not found.", (long unsigned int)nOffset );
                return NULL;
            }
            nOffset--;
        }

        nOffset = TIFFCurrentDirOffset( hTIFF );
    }


    GTiffDataset 	*poDS;

    poDS = new GTiffDataset();
    poDS->SetDescription( poOpenInfo->pszFilename );
    poDS->osFilename = poOpenInfo->pszFilename;
    poDS->poActiveDS = poDS;

    if( !EQUAL(pszFilename,poOpenInfo->pszFilename)
        && !EQUALN(poOpenInfo->pszFilename,"GTIFF_RAW:",10) )
    {
        poDS->SetPhysicalFilename( pszFilename );
        poDS->SetSubdatasetName( poOpenInfo->pszFilename );
        poDS->osFilename = pszFilename;
    }

    if (poOpenInfo->eAccess == GA_Update)
    {
        CPLError( CE_Warning, CPLE_AppDefined,
                  "Opening a specific TIFF directory is not supported in update mode. Switching to read-only" );
    }

    if( poDS->OpenOffset( hTIFF, &(poDS->poActiveDS),
                          nOffset, FALSE, GA_ReadOnly,
                          bAllowRGBAInterface, TRUE,
                          poOpenInfo->papszSiblingFiles ) != CE_None )
    {
        delete poDS;
        return NULL;
    }
    else
    {
        poDS->bCloseTIFFHandle = TRUE;
        return poDS;
    }
}
