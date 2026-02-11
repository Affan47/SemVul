WriteMpqDataMD5(
    TFileStream * pStream,
    ULONGLONG RawDataOffs,
    DWORD dwRawDataSize,
    DWORD dwChunkSize)
{
    hash_state md5_state;
    unsigned char * md5_array;
    unsigned char * md5;
    LPBYTE pbFileChunk;
    DWORD dwMd5ArraySize = 0;
    DWORD dwToRead = dwRawDataSize;
    int nError = ERROR_SUCCESS;


    md5_array = md5 = AllocateMd5Buffer(dwRawDataSize, dwChunkSize, &dwMd5ArraySize);
    if(md5_array == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;


    pbFileChunk = ALLOCMEM(BYTE, dwChunkSize);
    if(pbFileChunk == NULL)
    {
        FREEMEM(md5_array);
        return ERROR_NOT_ENOUGH_MEMORY;
    }


    while(dwRawDataSize != 0)
    {

        dwToRead = STORMLIB_MIN(dwRawDataSize, dwChunkSize);


        if(!FileStream_Read(pStream, &RawDataOffs, pbFileChunk, dwToRead))
        {
            nError = GetLastError();
            break;
        }


        md5_init(&md5_state);
        md5_process(&md5_state, (unsigned char *)pbFileChunk, dwToRead);
        md5_done(&md5_state, md5);
        md5 += MD5_DIGEST_SIZE;


        RawDataOffs += dwToRead;
        dwRawDataSize -= dwToRead;
    }


    if(nError == ERROR_SUCCESS)
    {
        if(!FileStream_Write(pStream, NULL, md5_array, dwMd5ArraySize))
            nError = GetLastError();
    }


    FREEMEM(pbFileChunk);
    FREEMEM(md5_array);
    return nError;
}
