OpenLocalFile(const char * szFileName, HANDLE * phFile)
{
    TFileStream * pStream;
    TMPQFile * hf = NULL;


#ifdef _UNICODE
    TCHAR szFileNameT[MAX_PATH];
    int i;

    for(i = 0; szFileName[i] != 0; i++)
        szFileNameT[i] = szFileName[i];
    szFileNameT[i] = 0;
    pStream = FileStream_OpenFile(szFileNameT, false);

#else
    pStream = FileStream_OpenFile(szFileName, false);
#endif

    if(pStream != NULL)
    {

        hf = CreateMpqFile(NULL);
        if(hf != NULL)
        {
            hf->pStream = pStream;
            *phFile = hf;
            return true;
        }
        else
        {
            FileStream_Close(pStream);
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        }
    }
    *phFile = NULL;
    return false;
}
