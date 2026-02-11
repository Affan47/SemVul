SFileGetFileName(HANDLE hFile, char * szFileName)
{
    TFileEntry * pFileEntry;
    TMPQFile * hf = (TMPQFile *)hFile;
    char szPseudoName[20];
    DWORD FirstBytes[2];
    DWORD dwFilePos;
    int nError = ERROR_SUCCESS;
    int i;


    if(szFileName != NULL)
        *szFileName = 0;


    if(!IsValidFileHandle(hf))
        nError = ERROR_INVALID_HANDLE;
    pFileEntry = hf->pFileEntry;


    if(nError == ERROR_SUCCESS && pFileEntry != NULL && pFileEntry->szFileName == NULL)
    {

        FirstBytes[0] = FirstBytes[1] = 0;
        dwFilePos = SFileSetFilePointer(hf, 0, NULL, FILE_CURRENT);
        SFileReadFile(hFile, FirstBytes, sizeof(FirstBytes), NULL);
        BSWAP_ARRAY32_UNSIGNED(FirstBytes, sizeof(FirstBytes));
        SFileSetFilePointer(hf, dwFilePos, NULL, FILE_BEGIN);


        for(i = 0; data2ext[i].szExt != NULL; i++)
        {
            if((FirstBytes[0] & data2ext[i].dwOffset00Mask) == data2ext[i].dwOffset00Data &&
               (FirstBytes[1] & data2ext[i].dwOffset04Mask) == data2ext[i].dwOffset04Data)
            {
                sprintf(szPseudoName, "File%08u.%s", (unsigned int)(pFileEntry - hf->ha->pFileTable), data2ext[i].szExt);
                break;
            }
        }


        AllocateFileName(pFileEntry, szPseudoName);
    }


    if(nError == ERROR_SUCCESS && szFileName != NULL)
    {
        if(pFileEntry != NULL && pFileEntry->szFileName != NULL)
            strcpy(szFileName, pFileEntry->szFileName);
        else if(hf->pStream != NULL)
            CopyFileName(szFileName, hf->pStream->szFileName);
    }
    return (nError == ERROR_SUCCESS);
}
