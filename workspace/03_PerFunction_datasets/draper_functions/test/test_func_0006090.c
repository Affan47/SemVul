Write( const void * pBuffer, size_t nSize, size_t nCount )

{
    if( !bUpdate )
    {
        errno = EACCES;
        return 0;
    }


    size_t nBytesToWrite = nSize * nCount;

    if( nBytesToWrite + nOffset > poFile->nLength )
    {
        if( !poFile->SetLength( nBytesToWrite + nOffset ) )
            return 0;
    }

    memcpy( poFile->pabyData + nOffset, pBuffer, nBytesToWrite );
    nOffset += nBytesToWrite;

    return nCount;
}
