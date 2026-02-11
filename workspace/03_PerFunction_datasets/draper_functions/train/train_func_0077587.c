pj_geocentric_to_geodetic( double a, double es,
                               long point_count, int point_offset,
                               double *x, double *y, double *z )

{
    double b;
    int    i;
    GeocentricInfo gi;

    if( es == 0.0 )
        b = a;
    else
        b = a * sqrt(1-es);

    if( pj_Set_Geocentric_Parameters( &gi, a, b ) != 0 )
    {
        pj_errno = PJD_ERR_GEOCENTRIC;
        return pj_errno;
    }

    for( i = 0; i < point_count; i++ )
    {
        long io = i * point_offset;

        if( x[io] == HUGE_VAL )
            continue;

        pj_Convert_Geocentric_To_Geodetic( &gi, x[io], y[io], z[io],
                                           y+io, x+io, z+io );
    }

    return 0;
}
