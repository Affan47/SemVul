GetGeoTransform( double *padfGeoTransform )
{
    if( padfGeoTransform == NULL )
        return CE_Failure;

    GS7BGRasterBand *poGRB = (GS7BGRasterBand *)GetRasterBand( 1 );

    if( poGRB == NULL )
    {
        padfGeoTransform[0] = 0;
        padfGeoTransform[1] = 1;
        padfGeoTransform[2] = 0;
        padfGeoTransform[3] = 0;
        padfGeoTransform[4] = 0;
        padfGeoTransform[5] = 1;
        return CE_Failure;
    }


    CPLPushErrorHandler( CPLQuietErrorHandler );
    CPLErr eErr = GDALPamDataset::GetGeoTransform( padfGeoTransform );
    CPLPopErrorHandler();

    if( eErr == CE_None )
        return CE_None;


    padfGeoTransform[1] = (poGRB->dfMaxX - poGRB->dfMinX)/(nRasterXSize - 1);
    padfGeoTransform[5] = (poGRB->dfMinY - poGRB->dfMaxY)/(nRasterYSize - 1);


    padfGeoTransform[0] = poGRB->dfMinX - padfGeoTransform[1] / 2;
    padfGeoTransform[3] = poGRB->dfMaxY - padfGeoTransform[5] / 2;


    padfGeoTransform[4] = 0.0;
    padfGeoTransform[2] = 0.0;

    return CE_None;
}
