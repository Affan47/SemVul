CreateJP2GeoTIFF()

{


    int         nGTBufSize = 0;
    unsigned char *pabyGTBuf = NULL;

    if( GTIFMemBufFromWkt( pszProjection, adfGeoTransform,
                           nGCPCount, pasGCPList,
                           &nGTBufSize, &pabyGTBuf ) != CE_None )
        return NULL;

    if( nGTBufSize == 0 )
        return NULL;


    GDALJP2Box *poBox;

    poBox = GDALJP2Box::CreateUUIDBox( msi_uuid2, nGTBufSize, pabyGTBuf );

    CPLFree( pabyGTBuf );

    return poBox;
}
