ReadGeometry( json_object* poObj )
{
    OGRGeometry* poGeometry = NULL;

    OGRwkbGeometryType eType = poLayer_->GetGeomType();
    if (eType == wkbPoint)
        poGeometry = OGRESRIJSONReadPoint( poObj );
    else if (eType == wkbLineString)
        poGeometry = OGRESRIJSONReadLineString( poObj );
    else if (eType == wkbPolygon)
        poGeometry = OGRESRIJSONReadPolygon( poObj );
    else if (eType == wkbMultiPoint)
        poGeometry = OGRESRIJSONReadMultiPoint( poObj );

    return poGeometry;
}
