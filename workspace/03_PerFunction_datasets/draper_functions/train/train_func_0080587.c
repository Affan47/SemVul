GDALRegister_L1B()

{
    GDALDriver  *poDriver;

    if( GDALGetDriverByName( "L1B" ) == NULL )
    {
        poDriver = new GDALDriver();

        poDriver->SetDescription( "L1B" );
        poDriver->SetMetadataItem( GDAL_DMD_LONGNAME,
                                   "NOAA Polar Orbiter Level 1b Data Set" );
        poDriver->SetMetadataItem( GDAL_DMD_HELPTOPIC,
                                   "frmt_l1b.html" );

        poDriver->SetMetadataItem( GDAL_DCAP_VIRTUALIO, "YES" );

        poDriver->pfnOpen = L1BDataset::Open;
        poDriver->pfnIdentify = L1BDataset::Identify;

        GetGDALDriverManager()->RegisterDriver( poDriver );
    }
}
