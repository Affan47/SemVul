GDALPipeRead(GDALPipe* p, char*** ppapszStr)
{
    int nStrCount;
    if( !GDALPipeRead(p, &nStrCount) )
        return FALSE;
    if( nStrCount < 0 )
    {
        *ppapszStr = NULL;
        return TRUE;
    }

    *ppapszStr = (char**) VSIMalloc2(sizeof(char*), (nStrCount + 1));
    if( *ppapszStr == NULL )
        return FALSE;
    for(int i=0;i<nStrCount;i++)
    {
        if( !GDALPipeRead(p, (*ppapszStr) + i) )
        {
            CSLDestroy(*ppapszStr);
            *ppapszStr = NULL;
            return FALSE;
        }
    }
    (*ppapszStr)[nStrCount] = NULL;
    return TRUE;
}
