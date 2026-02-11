GDALPipeWrite(GDALPipe* p, const void* data,
                                 int length)
{

    GByte* pCur = (GByte*) data;
    int nRemain = length;
    while( nRemain > 0 )
    {
        if( p->nBufferSize + nRemain <= BUFFER_SIZE )
        {
            memcpy(p->abyBuffer + p->nBufferSize, pCur, nRemain);
            pCur += nRemain;
            p->nBufferSize += nRemain;
            nRemain = 0;
        }
        else if( nRemain > BUFFER_SIZE )
        {
            if( !GDALPipeFlushBuffer(p) )
                return FALSE;
            if( !GDALPipeWrite_internal(p, pCur, nRemain) )
                return FALSE;
            pCur += nRemain;
            nRemain = 0;
        }
        else
        {
            memcpy(p->abyBuffer + p->nBufferSize, pCur,
                   BUFFER_SIZE - p->nBufferSize);
            pCur += (BUFFER_SIZE - p->nBufferSize);
            nRemain -= (BUFFER_SIZE - p->nBufferSize);
            p->nBufferSize = BUFFER_SIZE;
            if( !GDALPipeFlushBuffer(p) )
                return FALSE;
        }
    }
    return TRUE;
}
