AddFeature (const char* pszAptICAO,
                                            const char* pszText,
                                            double dfLat,
                                            double dfLon,
                                            double dfHeading,
                                            int nSize)
{
    int nCount = 0;
    OGRFeature* poFeature = new OGRFeature(poFeatureDefn);
    poFeature->SetField( nCount++, pszAptICAO );
    poFeature->SetField( nCount++, pszText );
    poFeature->SetGeometryDirectly( new OGRPoint( dfLon, dfLat ) );
    poFeature->SetField( nCount++, dfHeading );
    poFeature->SetField( nCount++, nSize );

    RegisterFeature(poFeature);

    return poFeature;
}
