EarlySetConfigOptions( int argc, char ** argv )
{


    for( int i = 1; i < argc; i++ )
    {
        if( EQUAL(argv[i],"--config") && i + 2 < argc &&
            (EQUAL(argv[i + 1], "GDAL_SKIP") ||
             EQUAL(argv[i + 1], "GDAL_DRIVER_PATH") ||
             EQUAL(argv[i + 1], "OGR_SKIP") ||
             EQUAL(argv[i + 1], "OGR_DRIVER_PATH")) )
        {
            CPLSetConfigOption( argv[i+1], argv[i+2] );

            i += 2;
        }
    }
}
