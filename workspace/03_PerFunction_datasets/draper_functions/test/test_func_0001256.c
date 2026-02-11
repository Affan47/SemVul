GetLayerByName( const char *pszName )

{
    CPLMutexHolderD( &m_hMutex );

    if ( ! pszName )
        return NULL;

    int  i;


    for( i = 0; i < GetLayerCount(); i++ )
    {
        OGRLayer *poLayer = GetLayer(i);

        if( strcmp( pszName, poLayer->GetName() ) == 0 )
            return poLayer;
    }


    for( i = 0; i < GetLayerCount(); i++ )
    {
        OGRLayer *poLayer = GetLayer(i);

        if( EQUAL( pszName, poLayer->GetName() ) )
            return poLayer;
    }

    return NULL;
}
