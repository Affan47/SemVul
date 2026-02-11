TestCapability( const char * pszCap )
{
    if( EQUAL(pszCap, OLCFastFeatureCount ) )
    {
        if( nFeatureCount >= 0 &&
            m_poFilterGeom == NULL && m_poAttrQuery == NULL )
            return TRUE;

        if( !GetAttrFilterPassThroughValue() )
            return FALSE;

        for(int i = 0; i < nSrcLayers; i++)
        {
            AutoWarpLayerIfNecessary(i);
            ApplyAttributeFilterToSrcLayer(i);
            papoSrcLayers[i]->SetSpatialFilter(m_poFilterGeom);
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCFastGetExtent ) )
    {
        if( sStaticEnvelope.IsInit() )
            return TRUE;

        for(int i = 0; i < nSrcLayers; i++)
        {
            AutoWarpLayerIfNecessary(i);
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCFastSpatialFilter) )
    {
        for(int i = 0; i < nSrcLayers; i++)
        {
            AutoWarpLayerIfNecessary(i);
            ApplyAttributeFilterToSrcLayer(i);
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCStringsAsUTF8) )
    {
        for(int i = 0; i < nSrcLayers; i++)
        {
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCRandomRead ) )
    {
        if( !bPreserveSrcFID )
            return FALSE;

        for(int i = 0; i < nSrcLayers; i++)
        {
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCRandomWrite ) )
    {
        if( !bPreserveSrcFID || osSourceLayerFieldName.size() == 0)
            return FALSE;

        for(int i = 0; i < nSrcLayers; i++)
        {
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCSequentialWrite ) )
    {
        if( osSourceLayerFieldName.size() == 0)
            return FALSE;

        for(int i = 0; i < nSrcLayers; i++)
        {
            if( !papoSrcLayers[i]->TestCapability(pszCap) )
                return FALSE;
        }
        return TRUE;
    }

    if( EQUAL(pszCap, OLCIgnoreFields) )
        return TRUE;

    return FALSE;
}
