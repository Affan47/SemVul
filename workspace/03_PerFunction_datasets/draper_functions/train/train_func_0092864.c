OGRGeoJSONReadMultiLineString( json_object* poObj )
{
    CPLAssert( NULL != poObj );

    OGRMultiLineString* poMultiLine = NULL;

    json_object* poObjLines = NULL;
    poObjLines = OGRGeoJSONFindMemberByName( poObj, "coordinates" );
    if( NULL == poObjLines )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Invalid MultiLineString object. "
                  "Missing \'coordinates\' member." );
        return NULL;
    }

    if( json_type_array == json_object_get_type( poObjLines ) )
    {
        const int nLines = json_object_array_length( poObjLines );

        poMultiLine = new OGRMultiLineString();

        for( int i = 0; i < nLines; ++i)
        {
            json_object* poObjLine = NULL;
            poObjLine = json_object_array_get_idx( poObjLines, i );

            OGRLineString* poLine;
            if (poObjLine != NULL)
                poLine = OGRGeoJSONReadLineString( poObjLine , true );
            else
                poLine = new OGRLineString();

            if( NULL != poLine )
            {
                poMultiLine->addGeometryDirectly( poLine );
            }
        }
    }

    return poMultiLine;
}
