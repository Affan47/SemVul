GDALPipeWrite(GDALPipe* p, char** papszStr)
{
    if( papszStr == NULL )
        return GDALPipeWrite(p, -1);

    int nCount = CSLCount(papszStr);
    if( !GDALPipeWrite(p, nCount) )
        return FALSE;
    for(int i=0; i < nCount; i++)
    {
        if( !GDALPipeWrite(p, papszStr[i]) )
            return FALSE;
    }
    return TRUE;
}
