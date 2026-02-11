GetNextFeature()

{
    if( (bHasPostGISGeometry || bHasPostGISGeography) && nSRSId == UNDETERMINED_SRID )
    {
        GetSpatialRef();
    }

    for( ; TRUE; )
    {
        OGRFeature      *poFeature;

        poFeature = GetNextRawFeature();
        if( poFeature == NULL )
            return NULL;

        if( (m_poFilterGeom == NULL
            || ((bHasPostGISGeometry || bHasPostGISGeography) && nSRSId != UNDETERMINED_SRID)
            || FilterGeometry( poFeature->GetGeometryRef() ) )
            && (m_poAttrQuery == NULL
                || m_poAttrQuery->Evaluate( poFeature )) )
            return poFeature;

        delete poFeature;
    }
}
