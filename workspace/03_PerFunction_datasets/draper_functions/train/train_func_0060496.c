SyncToDisk()

{
    CPLMutexHolderD( &m_hMutex );
    int i;
    OGRErr eErr;

    for( i = 0; i < GetLayerCount(); i++ )
    {
        OGRLayer *poLayer = GetLayer(i);

        if( poLayer )
        {
            eErr = poLayer->SyncToDisk();
            if( eErr != OGRERR_NONE )
                return eErr;
        }
    }

    return OGRERR_NONE;
}
