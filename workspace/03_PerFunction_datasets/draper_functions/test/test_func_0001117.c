DTEDSetMetadata( DTEDInfo *psDInfo, DTEDMetaDataCode eCode,
                     const char *pszNewValue )

{
    int nFieldLen;
    char *pszFieldSrc;

    if( !psDInfo->bUpdate )
        return FALSE;


    DTEDGetMetadataLocation( psDInfo, eCode, &pszFieldSrc, &nFieldLen );
    if( pszFieldSrc == NULL )
        return FALSE;


    memset( pszFieldSrc, ' ', nFieldLen );
    strncpy( pszFieldSrc, pszNewValue,
             MIN((size_t)nFieldLen,strlen(pszNewValue)) );


    psDInfo->bRewriteHeaders = TRUE;

    return TRUE;
}
