SetGeoTransform( double *padfTransform )
{
    if( GDALPamDataset::SetGeoTransform( padfTransform ) != CE_None )
    {
        memcpy( adfGeoTransform, padfTransform, sizeof( double ) * 6 );
    }

    INGR_SetTransMatrix( hHeaderOne.TransformationMatrix, padfTransform );

    return CE_None;
}
