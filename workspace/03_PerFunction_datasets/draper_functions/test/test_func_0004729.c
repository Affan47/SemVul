Decompress_LZMA(char * pbOutBuffer, int * pcbOutBuffer, char * pbInBuffer, int cbInBuffer)
{
    ELzmaStatus LzmaStatus;
    ISzAlloc SzAlloc;
    Byte * destBuffer = (Byte *)pbOutBuffer;
    Byte * srcBuffer = (Byte *)pbInBuffer;
    SizeT destLen = *pcbOutBuffer;
    SizeT srcLen = cbInBuffer;
    SRes nResult;


    if(srcLen <= LZMA_HEADER_SIZE)
        return 0;


    if(*srcBuffer != 0)
        return 0;


    SzAlloc.Alloc = LZMA_Callback_Alloc;
    SzAlloc.Free = LZMA_Callback_Free;


    srcLen = cbInBuffer - LZMA_HEADER_SIZE;
    nResult = LzmaDecode(destBuffer,
                        &destLen,
                         srcBuffer + LZMA_HEADER_SIZE,
                        &srcLen,
                         srcBuffer + 1,
                         LZMA_PROPS_SIZE,
                         LZMA_FINISH_END,
                        &LzmaStatus,
                        &SzAlloc);
    if(nResult != SZ_OK)
        return 0;

    *pcbOutBuffer = (unsigned int)destLen;
    return 1;
}
