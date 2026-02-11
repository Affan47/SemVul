Set1DGeolocation( int nVarId, const char *szDimName )
{
    char    szTemp[ NCDF_MAX_STR_LEN ];
    char    *pszVarValues = NULL;
    CPLErr eErr;


    eErr = NCDFGet1DVar( cdfid, nVarId, &pszVarValues );
    if ( eErr != CE_None )
        return eErr;


    sprintf( szTemp, "%s_VALUES", szDimName );
    SetMetadataItem( szTemp, pszVarValues, "GEOLOCATION2" );

    CPLFree( pszVarValues );

    return CE_None;
}
