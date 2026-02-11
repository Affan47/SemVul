GDALIdentifyDriver( const char * pszFilename,
                    char **papszFileList )

{
    int         	iDriver;
    GDALDriverManager  *poDM = GetGDALDriverManager();
    GDALOpenInfo        oOpenInfo( pszFilename, GA_ReadOnly, papszFileList );
    CPLLocaleC          oLocaleForcer;

    CPLErrorReset();
    CPLAssert( NULL != poDM );

    for( iDriver = -1; iDriver < poDM->GetDriverCount(); iDriver++ )
    {
        GDALDriver      *poDriver;
        GDALDataset     *poDS;

        if( iDriver < 0 )
            poDriver = GDALGetAPIPROXYDriver();
        else
            poDriver = poDM->GetDriver( iDriver );

        VALIDATE_POINTER1( poDriver, "GDALIdentifyDriver", NULL );

        if( poDriver->pfnIdentify != NULL )
        {
            if( poDriver->pfnIdentify( &oOpenInfo ) )
                return (GDALDriverH) poDriver;
        }
        else if( poDriver->pfnOpen != NULL )
        {
            poDS = poDriver->pfnOpen( &oOpenInfo );
            if( poDS != NULL )
            {
                delete poDS;
                return (GDALDriverH) poDriver;
            }

            if( CPLGetLastErrorNo() != 0 )
                return NULL;
        }
    }

    return NULL;
}
