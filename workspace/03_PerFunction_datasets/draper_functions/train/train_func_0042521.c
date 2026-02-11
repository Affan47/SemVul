AddFeature(const char* pszNavaidID,
                                   const char* pszNavaidName,
                                   const char* pszSubType,
                                   double dfLat,
                                   double dfLon,
                                   double dfEle,
                                   double dfFreq,
                                   double dfRange,
                                   double dfBias)
{
    int nCount = 0;
    OGRFeature* poFeature = new OGRFeature(poFeatureDefn);
    poFeature->SetGeometryDirectly( new OGRPoint( dfLon, dfLat ) );
    poFeature->SetField( nCount++, pszNavaidID );
    poFeature->SetField( nCount++, pszNavaidName );
    poFeature->SetField( nCount++, pszSubType );
    poFeature->SetField( nCount++, dfEle );
    poFeature->SetField( nCount++, dfFreq );
    poFeature->SetField( nCount++, dfRange );
    poFeature->SetField( nCount++, dfBias );

    RegisterFeature(poFeature);

    return poFeature;
}
