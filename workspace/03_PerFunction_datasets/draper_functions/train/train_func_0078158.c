GDALRegister_DOQ2()

{
    GDALDriver	*poDriver;

    if( GDALGetDriverByName( "DOQ2" ) == NULL )
    {
        poDriver = new GDALDriver();

        poDriver->SetDescription( "DOQ2" );
        poDriver->SetMetadataItem( GDAL_DMD_LONGNAME,
                                   "USGS DOQ (New Style)" );
        poDriver->SetMetadataItem( GDAL_DMD_HELPTOPIC,
                                   "frmt_various.html#DOQ2" );
        poDriver->SetMetadataItem( GDAL_DCAP_VIRTUALIO, "YES" );

        poDriver->pfnOpen = DOQ2Dataset::Open;

        GetGDALDriverManager()->RegisterDriver( poDriver );
    }
}
