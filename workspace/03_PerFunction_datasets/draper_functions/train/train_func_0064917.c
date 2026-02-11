EncryptedFile_Read(
    TEncryptedStream * pStream,
    ULONGLONG * pByteOffset,
    void * pvBuffer,
    DWORD dwBytesToRead)
{
    ULONGLONG StartOffset;
    ULONGLONG ByteOffset;
    ULONGLONG EndOffset;
    DWORD dwBytesToAllocate;
    DWORD dwBytesToDecrypt;
    DWORD dwOffsetInCache;
    LPBYTE pbMpqData = NULL;
    bool bResult = false;


    if(pByteOffset != NULL)
        ByteOffset = *pByteOffset;
    else
        ByteOffset = pStream->RawFilePos;


    StartOffset = ByteOffset;
    StartOffset = StartOffset & ~(MPQE_CHUNK_SIZE - 1);
    EndOffset = ByteOffset + dwBytesToRead;


    dwBytesToDecrypt = (DWORD)(EndOffset - StartOffset);
    dwBytesToAllocate = (dwBytesToDecrypt + (MPQE_CHUNK_SIZE - 1)) & ~(MPQE_CHUNK_SIZE - 1);


    pbMpqData = ALLOCMEM(BYTE, dwBytesToAllocate);
    if(pbMpqData)
    {

        dwOffsetInCache = (DWORD)(ByteOffset - StartOffset);


        if(File_Read(pStream, &StartOffset, pbMpqData, dwBytesToDecrypt))
        {

            DecryptFileChunk((LPDWORD)pbMpqData, pStream->Key, StartOffset, dwBytesToAllocate);


            memcpy(pvBuffer, pbMpqData + dwOffsetInCache, dwBytesToRead);
            bResult = true;
        }
        else
        {
            assert(false);
        }


        FREEMEM(pbMpqData);
    }


    return bResult;
}
