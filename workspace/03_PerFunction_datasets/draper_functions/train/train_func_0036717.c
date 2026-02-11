GDALPipeRead(GDALPipe* p, char** ppszStr)
{
    int nLength;
    if( !GDALPipeRead(p, &nLength) || nLength < 0 )
    {
        *ppszStr = NULL;
        return FALSE;
    }
    if( nLength == 0 )
    {
        *ppszStr = NULL;
        return TRUE;
    }
    *ppszStr = (nLength < INT_MAX-1) ? (char*) VSIMalloc(nLength + 1) : NULL;
    if( *ppszStr == NULL )
        return FALSE;
    if( nLength > 0 && !GDALPipeRead_nolength(p, nLength, *ppszStr) )
    {
        CPLFree(*ppszStr);
        *ppszStr = NULL;
        return FALSE;
    }
    (*ppszStr)[nLength] = 0;
    return TRUE;
}
