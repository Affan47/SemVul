OGRGeoJSONWritePolygon( OGRPolygon* poPolygon, int nCoordPrecision )
{
    CPLAssert( NULL != poPolygon );


    json_object* poObj = NULL;
    poObj = json_object_new_array();


    OGRLinearRing* poRing = poPolygon->getExteriorRing();
    if (poRing == NULL)
        return poObj;

    json_object* poObjRing = NULL;
    poObjRing = OGRGeoJSONWriteLineCoords( poRing, nCoordPrecision );
    json_object_array_add( poObj, poObjRing );


    const int nCount = poPolygon->getNumInteriorRings();
    for( int i = 0; i < nCount; ++i )
    {
        poRing = poPolygon->getInteriorRing( i );
        if (poRing == NULL)
            continue;

        poObjRing = OGRGeoJSONWriteLineCoords( poRing, nCoordPrecision );

        json_object_array_add( poObj, poObjRing );
    }

    return poObj;
}
