SetAttributeFilter( const char *pszNewQuery )

{
    if (!bHasFullInitialized) FullInitialize();
    if (!poSrcLayer || poDS->GetRecursionDetected()) return OGRERR_FAILURE;

    if( bAttrFilterPassThrough )
    {
        CPLFree( pszAttrFilter );
        if( pszNewQuery == NULL || strlen(pszNewQuery) == 0 )
            pszAttrFilter = NULL;
        else
            pszAttrFilter = CPLStrdup( pszNewQuery );

        ResetReading();
        return OGRERR_NONE;
    }
    else
    {

        return OGRLayer::SetAttributeFilter( pszNewQuery );
    }
}
