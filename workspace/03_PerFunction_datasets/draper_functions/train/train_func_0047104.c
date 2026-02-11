CPLWriteFct(void *buffer, size_t size, size_t nmemb, void *reqInfo)

{
    CPLHTTPResult *psResult = (CPLHTTPResult *) reqInfo;
    int  nNewSize;

    nNewSize = psResult->nDataLen + nmemb*size + 1;
    if( nNewSize > psResult->nDataAlloc )
    {
        psResult->nDataAlloc = (int) (nNewSize * 1.25 + 100);
        GByte* pabyNewData = (GByte *) VSIRealloc(psResult->pabyData,
                                                  psResult->nDataAlloc);
        if( pabyNewData == NULL )
        {
            VSIFree(psResult->pabyData);
            psResult->pabyData = NULL;
            psResult->pszErrBuf = CPLStrdup(CPLString().Printf("Out of memory allocating %d bytes for HTTP data buffer.", psResult->nDataAlloc));
            psResult->nDataAlloc = psResult->nDataLen = 0;

            return 0;
        }
        psResult->pabyData = pabyNewData;
    }

    memcpy( psResult->pabyData + psResult->nDataLen, buffer,
            nmemb * size );

    psResult->nDataLen += nmemb * size;
    psResult->pabyData[psResult->nDataLen] = 0;

    return nmemb;
}
