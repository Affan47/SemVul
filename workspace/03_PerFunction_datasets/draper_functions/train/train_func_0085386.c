CreateFeature( OGRFeature *poFeature )

{
    char        szRecord[OGR_TIGER_RECBUF_LEN];


    if( !SetWriteModule( "A", psRTAInfo->nRecordLength+2, poFeature ) )
        return OGRERR_FAILURE;

    memset( szRecord, ' ', psRTAInfo->nRecordLength );

    WriteFields( psRTAInfo, poFeature, szRecord );
    WriteRecord( szRecord, psRTAInfo->nRecordLength, "A" );


    memset( szRecord, ' ', psRTSInfo->nRecordLength );

    WriteFields( psRTSInfo, poFeature, szRecord );
    WriteRecord( szRecord, psRTSInfo->nRecordLength, "S", fpRTS );


    return OGRERR_NONE;
}
