CPLZLibDeflate( const void* ptr, size_t nBytes, int nLevel,
                      void* outptr, size_t nOutAvailableBytes,
                      size_t* pnOutBytes )
{
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK)
    {
        if( pnOutBytes != NULL )
            *pnOutBytes = 0;
        return NULL;
    }

    size_t nTmpSize;
    void* pTmp;
    if( outptr == NULL )
    {
        nTmpSize = 8 + nBytes * 2;
        pTmp = VSIMalloc(nTmpSize);
        if( pTmp == NULL )
        {
            deflateEnd(&strm);
            if( pnOutBytes != NULL )
                *pnOutBytes = 0;
            return NULL;
        }
    }
    else
    {
        pTmp = outptr;
        nTmpSize = nOutAvailableBytes;
    }

    strm.avail_in = nBytes;
    strm.next_in = (Bytef*) ptr;
    strm.avail_out = nTmpSize;
    strm.next_out = (Bytef*) pTmp;
    ret = deflate(&strm, Z_FINISH);
    if( ret != Z_STREAM_END )
    {
        if( pTmp != outptr )
            VSIFree(pTmp);
        if( pnOutBytes != NULL )
            *pnOutBytes = 0;
        return NULL;
    }
    if( pnOutBytes != NULL )
        *pnOutBytes = nTmpSize - strm.avail_out;
    deflateEnd(&strm);
    return pTmp;
}
