PamInitialize()

{
#ifdef PAM_ENABLED
    static const char *pszPamDefault = "YES";
#else
    static const char *pszPamDefault = "NO";
#endif

    if( psPam || (nPamFlags & GPF_DISABLED) )
        return;

    if( !CSLTestBoolean( CPLGetConfigOption( "GDAL_PAM_ENABLED",
                                             pszPamDefault ) ) )
    {
        nPamFlags |= GPF_DISABLED;
        return;
    }


    if( EQUAL( CPLGetConfigOption( "GDAL_PAM_MODE", "PAM" ), "AUX") )
        nPamFlags |= GPF_AUXMODE;

    psPam = new GDALDatasetPamInfo;
    psPam->pszPamFilename = NULL;
    psPam->pszProjection = NULL;
    psPam->bHaveGeoTransform = FALSE;
    psPam->nGCPCount = 0;
    psPam->pasGCPList = NULL;
    psPam->pszGCPProjection = NULL;

    int iBand;

    for( iBand = 0; iBand < GetRasterCount(); iBand++ )
    {
        GDALPamRasterBand *poBand = (GDALPamRasterBand *)
            GetRasterBand(iBand+1);

        if( poBand == NULL || !(poBand->GetMOFlags() & GMO_PAM_CLASS) )
            continue;

        poBand->PamInitialize();
    }
}
