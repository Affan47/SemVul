InstallGeoTIFF(const char *geofile, const char *tiffile)
{
    TIFF *tif = (TIFF*)0;
    GTIF *gtif=(GTIF*)0;
    FILE *fp;

    uint16 *panVI = NULL;
    uint16 nKeyCount;

    tif = XTIFFOpen(tiffile, "r+");
    if (!tif)
    {
        perror(tiffile);
        fprintf(stderr, "Cannot open TIFF file %s (does not exist or not a valid TIFF file)\n", tiffile);
        return(-1);
    }


    if( TIFFGetField( tif, TIFFTAG_GEOKEYDIRECTORY,
                      &nKeyCount, &panVI ) )
    {
        uint16 anGKVersionInfo[4] = { 1, 1, 0, 0 };
        double  adfDummyDoubleParams[1] = { 0.0 };

        TIFFSetField( tif, TIFFTAG_GEOKEYDIRECTORY,
                      4, anGKVersionInfo );
        TIFFSetField( tif, TIFFTAG_GEODOUBLEPARAMS,
                      1, adfDummyDoubleParams );
        TIFFSetField( tif, TIFFTAG_GEOASCIIPARAMS, "" );
    }

    gtif = GTIFNew(tif);
    if (!gtif)
    {
        fprintf(stderr, "Internal error (GTIFNew)\n");
        return(-2);
    }


    fp = fopen(geofile, "r");
    if( fp == NULL )
    {
        perror( geofile );
        fprintf(stderr, "Cannot open projection definition file %s\n", geofile);
        return(-3);
    }
    if (!GTIFImport(gtif, 0, fp))
    {
        fprintf(stderr,"Projection definition file is not valid (%s)\n", geofile);
        return(-4);
    }
    fclose(fp);


    GTIFWriteKeys(gtif);


    GTIFFree(gtif);
    TIFFRewriteDirectory(tif);
    XTIFFClose(tif);
    return(0);
}
