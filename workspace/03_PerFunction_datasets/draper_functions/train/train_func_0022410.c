LoadCutline( const char *pszCutlineDSName, const char *pszCLayer,
             const char *pszCWHERE, const char *pszCSQL,
             void **phCutlineRet )

{
#ifndef OGR_ENABLED
    CPLError( CE_Failure, CPLE_AppDefined,
              "Request to load a cutline failed, this build does not support OGR features.\n" );
    GDALExit( 1 );
#else
    OGRRegisterAll();


    OGRDataSourceH hSrcDS;

    hSrcDS = OGROpen( pszCutlineDSName, FALSE, NULL );
    if( hSrcDS == NULL )
        GDALExit( 1 );


    OGRLayerH hLayer = NULL;

    if( pszCSQL != NULL )
        hLayer = OGR_DS_ExecuteSQL( hSrcDS, pszCSQL, NULL, NULL );
    else if( pszCLayer != NULL )
        hLayer = OGR_DS_GetLayerByName( hSrcDS, pszCLayer );
    else
        hLayer = OGR_DS_GetLayer( hSrcDS, 0 );

    if( hLayer == NULL )
    {
        fprintf( stderr, "Failed to identify source layer from datasource.\n" );
        GDALExit( 1 );
    }


    if( pszCWHERE != NULL )
        OGR_L_SetAttributeFilter( hLayer, pszCWHERE );


    OGRFeatureH hFeat;
    OGRGeometryH hMultiPolygon = OGR_G_CreateGeometry( wkbMultiPolygon );

    OGR_L_ResetReading( hLayer );

    while( (hFeat = OGR_L_GetNextFeature( hLayer )) != NULL )
    {
        OGRGeometryH hGeom = OGR_F_GetGeometryRef(hFeat);

        if( hGeom == NULL )
        {
            fprintf( stderr, "ERROR: Cutline feature without a geometry.\n" );
            GDALExit( 1 );
        }

        OGRwkbGeometryType eType = wkbFlatten(OGR_G_GetGeometryType( hGeom ));

        if( eType == wkbPolygon )
            OGR_G_AddGeometry( hMultiPolygon, hGeom );
        else if( eType == wkbMultiPolygon )
        {
            int iGeom;

            for( iGeom = 0; iGeom < OGR_G_GetGeometryCount( hGeom ); iGeom++ )
            {
                OGR_G_AddGeometry( hMultiPolygon,
                                   OGR_G_GetGeometryRef(hGeom,iGeom) );
            }
        }
        else
        {
            fprintf( stderr, "ERROR: Cutline not of polygon type.\n" );
            GDALExit( 1 );
        }

        OGR_F_Destroy( hFeat );
    }

    if( OGR_G_GetGeometryCount( hMultiPolygon ) == 0 )
    {
        fprintf( stderr, "ERROR: Did not get any cutline features.\n" );
        GDALExit( 1 );
    }


    OGR_G_AssignSpatialReference(
        hMultiPolygon, OGR_L_GetSpatialRef(hLayer) );

    *phCutlineRet = (void *) hMultiPolygon;


    if( pszCSQL != NULL )
        OGR_DS_ReleaseResultSet( hSrcDS, hLayer );

    OGR_DS_Destroy( hSrcDS );
#endif
}
