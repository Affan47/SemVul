CreateFeature( OGRFeature *poFeature )

{
    char        szRecord[OGR_TIGER_RECBUF_LEN];

    if (psRTInfo == NULL)
        return OGRERR_FAILURE;

    if( !SetWriteModule( m_pszFileCode, psRTInfo->nRecordLength+2, poFeature ) )
        return OGRERR_FAILURE;

    memset( szRecord, ' ', psRTInfo->nRecordLength );

    WriteFields( psRTInfo, poFeature, szRecord );

    WriteRecord( szRecord, psRTInfo->nRecordLength, m_pszFileCode );

    return OGRERR_NONE;
}
