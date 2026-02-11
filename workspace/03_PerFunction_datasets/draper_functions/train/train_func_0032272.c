AddGridMappingRef( )
{
    int nVarId = -1;
    int bOldDefineMode = bDefineMode;

    if( (GetAccess() == GA_Update) &&
        (nBands >= 1) && (GetRasterBand( 1 )) &&
        pszCFProjection != NULL && ! EQUAL( pszCFProjection, "" ) ) {

        nVarId = ( (netCDFRasterBand *) GetRasterBand( 1 ) )->nZId;
        bAddedGridMappingRef = TRUE;


        SetDefineMode( TRUE );
        status = nc_put_att_text( cdfid, nVarId,
                                  CF_GRD_MAPPING,
                                  strlen( pszCFProjection ),
                                  pszCFProjection );
        NCDF_ERR(status);
        if ( pszCFCoordinates != NULL && ! EQUAL( pszCFCoordinates, "" ) ) {
            status = nc_put_att_text( cdfid, nVarId,
                                      CF_COORDINATES,
                                      strlen( pszCFCoordinates ),
                                      pszCFCoordinates );
            NCDF_ERR(status);
        }


        SetDefineMode( bOldDefineMode );
    }
}
