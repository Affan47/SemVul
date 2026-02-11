GetGeoTransform( double * padfTransform )

{
    if (!bHasLoadedProjection)
        LoadProjection();
    memcpy( padfTransform, adfGeoTransform, sizeof(double)*6 );
    return CE_None;
}
