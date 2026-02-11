GetNextFeature()

{
    if (!bHasFullInitialized) FullInitialize();
    if (!poSrcLayer || poDS->GetRecursionDetected()) return NULL;

    if( bNeedReset )
    {
        if( !ResetSourceReading() )
            return NULL;
    }

    for( ; TRUE; )
    {
        OGRFeature      *poSrcFeature, *poFeature;

        poSrcFeature = poSrcLayer->GetNextFeature();
        if( poSrcFeature == NULL )
            return NULL;

        if (poFeatureDefn == poSrcFeatureDefn)
        {
            poFeature = poSrcFeature;
            ClipAndAssignSRS(poFeature);
        }
        else
        {
            poFeature = TranslateFeature( poSrcFeature, TRUE );
            delete poSrcFeature;
        }

        if( poFeature == NULL )
            return NULL;

        if( (eGeometryStyle == VGS_Direct || m_poFilterGeom == NULL
            || FilterGeometry( poFeature->GetGeometryRef() ) )
            && (m_poAttrQuery == NULL
                || m_poAttrQuery->Evaluate( poFeature )) )
            return poFeature;

        delete poFeature;
    }
}
