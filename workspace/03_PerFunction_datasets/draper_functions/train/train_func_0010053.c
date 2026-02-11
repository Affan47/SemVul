Finalize()
{
    if (bIsFinalized)
        return FALSE;

    int bHasDroppedRef = FALSE;

    Crystalize();


    if( CSLTestBoolean(CPLGetConfigOption( "ESRI_XML_PAM", "NO" )) )
    {
        char **papszESRIMD = GetMetadata("xml:ESRI");
        if( papszESRIMD )
        {
            GDALPamDataset::SetMetadata( papszESRIMD, "xml:ESRI");
        }
    }


    GDALPamDataset::FlushCache();


    if( bFillEmptyTiles )
    {
        FillEmptyTiles();
        bFillEmptyTiles = FALSE;
    }


    FlushCache();


    if( bMetadataChanged )
    {
        PushMetadataToPam();
        bMetadataChanged = FALSE;
        GDALPamDataset::FlushCache();
    }


    if( bBase )
    {
        for( int i = 0; i < nOverviewCount; i++ )
        {
            delete papoOverviewDS[i];
            bHasDroppedRef = TRUE;
        }
        nOverviewCount = 0;
    }


    CPLFree( papoOverviewDS );
    papoOverviewDS = NULL;


    if (poMaskDS)
    {
        delete poMaskDS;
        poMaskDS = NULL;
        bHasDroppedRef = TRUE;
    }

    if( poColorTable != NULL )
        delete poColorTable;
    poColorTable = NULL;

    if( bBase || bCloseTIFFHandle )
    {
        XTIFFClose( hTIFF );
        hTIFF = NULL;
    }

    if( nGCPCount > 0 )
    {
        GDALDeinitGCPs( nGCPCount, pasGCPList );
        CPLFree( pasGCPList );
        pasGCPList = NULL;
        nGCPCount = 0;
    }

    CPLFree( pszProjection );
    pszProjection = NULL;

    CSLDestroy( papszCreationOptions );
    papszCreationOptions = NULL;

    CPLFree(pabyTempWriteBuffer);
    pabyTempWriteBuffer = NULL;

    if( *ppoActiveDSRef == this )
        *ppoActiveDSRef = NULL;
    ppoActiveDSRef = NULL;

    bIsFinalized = TRUE;

    return bHasDroppedRef;
}
