OGRMergeGeometryTypes( OGRwkbGeometryType eMain,
                       OGRwkbGeometryType eExtra )

{
    int n25DFlag = 0;
    OGRwkbGeometryType eFMain = wkbFlatten(eMain);
    OGRwkbGeometryType eFExtra = wkbFlatten(eExtra);

    if( eFMain != eMain || eFExtra != eExtra )
        n25DFlag = wkb25DBit;

    if( eFMain == wkbUnknown || eFExtra == wkbUnknown )
        return (OGRwkbGeometryType) (((int) wkbUnknown) | n25DFlag);

    if( eFMain == wkbNone )
        return eExtra;

    if( eFExtra == wkbNone )
        return eMain;

    if( eFMain == eFExtra )
        return (OGRwkbGeometryType) (((int) eFMain) | n25DFlag);


    if( (eFMain == wkbGeometryCollection
         || eFMain == wkbMultiPoint
         || eFMain == wkbMultiLineString
         || eFMain == wkbMultiPolygon)
        && (eFExtra == wkbGeometryCollection
            || eFExtra == wkbMultiPoint
            || eFExtra == wkbMultiLineString
            || eFMain == wkbMultiPolygon) )
    {
        return (OGRwkbGeometryType) (((int) wkbGeometryCollection) | n25DFlag);
    }


    return (OGRwkbGeometryType) (((int) wkbUnknown) | n25DFlag);
}
