GDALCreateReprojectionTransformer( const char *pszSrcWKT,
                                         const char *pszDstWKT )

{
    OGRSpatialReference oSrcSRS, oDstSRS;
    OGRCoordinateTransformation *poForwardTransform;


    if( oSrcSRS.importFromWkt( (char **) &pszSrcWKT ) != OGRERR_NONE )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Failed to import coordinate system `%s'.",
                  pszSrcWKT );
        return NULL;
    }
    if( oDstSRS.importFromWkt( (char **) &pszDstWKT ) != OGRERR_NONE )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Failed to import coordinate system `%s'.",
                  pszSrcWKT );
        return NULL;
    }


    poForwardTransform = OGRCreateCoordinateTransformation(&oSrcSRS,&oDstSRS);

    if( poForwardTransform == NULL )

        return NULL;


    GDALReprojectionTransformInfo *psInfo;

    psInfo = (GDALReprojectionTransformInfo *)
        CPLCalloc(sizeof(GDALReprojectionTransformInfo),1);

    psInfo->poForwardTransform = poForwardTransform;
    psInfo->poReverseTransform =
        OGRCreateCoordinateTransformation(&oDstSRS,&oSrcSRS);

    strcpy( psInfo->sTI.szSignature, "GTI" );
    psInfo->sTI.pszClassName = "GDALReprojectionTransformer";
    psInfo->sTI.pfnTransform = GDALReprojectionTransform;
    psInfo->sTI.pfnCleanup = GDALDestroyReprojectionTransformer;
    psInfo->sTI.pfnSerialize = GDALSerializeReprojectionTransformer;

    return psInfo;
}
