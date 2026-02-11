SetProjection(const char* _pszProjection)

{
    int    bNorth;
    OGRSpatialReference oSRS, oSRS_WGS84;
    char *pszWKT = (char *) _pszProjection;

    if( pszWKT != NULL )
        oSRS.importFromWkt( &pszWKT );
    else
        return CE_Failure;

    oSRS_WGS84.SetWellKnownGeogCS( "WGS84" );
    if ( oSRS.IsSameGeogCS(&oSRS_WGS84) == FALSE)
    {
        CPLError(CE_Failure, CPLE_NotSupported,
                 "NITF only supports WGS84 geographic and UTM projections.\n");
        return CE_Failure;
    }

    if( oSRS.IsGeographic() && oSRS.GetPrimeMeridian() == 0.0)
    {
        if (psImage->chICORDS != 'G' && psImage->chICORDS != 'D')
        {
            CPLError(CE_Failure, CPLE_NotSupported,
                     "NITF file should have been created with creation option 'ICORDS=G' (or 'ICORDS=D').\n");
            return CE_Failure;
        }
    }
    else if( oSRS.GetUTMZone( &bNorth ) > 0)
    {
        if (bNorth && psImage->chICORDS != 'N')
        {
            CPLError(CE_Failure, CPLE_NotSupported,
                     "NITF file should have been created with creation option 'ICORDS=N'.\n");
            return CE_Failure;
        }
        else if (!bNorth && psImage->chICORDS != 'S')
        {
            CPLError(CE_Failure, CPLE_NotSupported,
                     "NITF file should have been created with creation option 'ICORDS=S'.\n");
            return CE_Failure;
        }

        psImage->nZone = oSRS.GetUTMZone( NULL );
    }
    else
    {
        CPLError(CE_Failure, CPLE_NotSupported,
                 "NITF only supports WGS84 geographic and UTM projections.\n");
        return CE_Failure;
    }

    CPLFree(pszProjection);
    pszProjection = CPLStrdup(_pszProjection);

    if (bGotGeoTransform)
        SetGeoTransform(adfGeoTransform);

    return CE_None;
}
