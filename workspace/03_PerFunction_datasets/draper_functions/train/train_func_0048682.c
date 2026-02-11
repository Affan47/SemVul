CreateLayer( const char * pszLayerName,
                                          OGRSpatialReference *poSRS,
                                          OGRwkbGeometryType eType,
                                          char ** papszOptions )

{
    BNAFeatureType bnaFeatureType;

    switch(eType)
    {
        case wkbPolygon:
        case wkbPolygon25D:
        case wkbMultiPolygon:
        case wkbMultiPolygon25D:
            bnaFeatureType = BNA_POLYGON;
            break;

        case wkbPoint:
        case wkbPoint25D:
            bnaFeatureType = BNA_POINT;
            break;

        case wkbLineString:
        case wkbLineString25D:
            bnaFeatureType = BNA_POLYLINE;
            break;

        default:
            CPLError( CE_Failure, CPLE_NotSupported,
                    "Geometry type of `%s' not supported in BNAs.\n",
                    OGRGeometryTypeToName(eType) );
            return NULL;
    }

    nLayers++;
    papoLayers = (OGRBNALayer **) CPLRealloc(papoLayers, nLayers * sizeof(OGRBNALayer*));
    papoLayers[nLayers-1] = new OGRBNALayer( pszName, pszLayerName, bnaFeatureType, eType, TRUE, this );

    return papoLayers[nLayers-1];
}
