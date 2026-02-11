SFileExtractFile(HANDLE hMpq, const char * szToExtract, const TCHAR * szExtracted, DWORD dwSearchScope)
{
    TFileStream * pLocalFile = NULL;
    HANDLE hMpqFile = NULL;
    int nError = ERROR_SUCCESS;


    if(nError == ERROR_SUCCESS)
    {
        if(!SFileOpenFileEx(hMpq, szToExtract, dwSearchScope, &hMpqFile))
            nError = GetLastError();
    }


    if(nError == ERROR_SUCCESS)
    {
        pLocalFile = FileStream_CreateFile(szExtracted);
        if(pLocalFile == NULL)
            nError = GetLastError();
    }


    if(nError == ERROR_SUCCESS)
    {
        char  szBuffer[0x1000];
        DWORD dwTransferred;

        for(;;)
        {


            if(!SFileReadFile(hMpqFile, szBuffer, sizeof(szBuffer), &dwTransferred, NULL))
                nError = GetLastError();
            if(nError == ERROR_HANDLE_EOF)
                nError = ERROR_SUCCESS;
            if(dwTransferred == 0)
                break;


            if(!FileStream_Write(pLocalFile, NULL, szBuffer, dwTransferred))
                nError = GetLastError();
        }
    }


    if(hMpqFile != NULL)
        SFileCloseFile(hMpqFile);
    if(pLocalFile != NULL)
        FileStream_Close(pLocalFile);
    if(nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}
