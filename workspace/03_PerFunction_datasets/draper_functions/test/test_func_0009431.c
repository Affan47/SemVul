SFileRenameFile(HANDLE hMpq, const char * szFileName, const char * szNewFileName)
{
    TMPQArchive * ha = (TMPQArchive *)hMpq;
    TFileEntry * pFileEntry = NULL;
    ULONGLONG RawDataOffs;
    TMPQFile * hf;
    int nError = ERROR_SUCCESS;


    if(nError == ERROR_SUCCESS)
    {
        if(!IsValidMpqHandle(ha))
            nError = ERROR_INVALID_HANDLE;
        if(szFileName == NULL || *szFileName == 0 || szNewFileName == NULL || *szNewFileName == 0)
            nError = ERROR_INVALID_PARAMETER;
    }

    if(nError == ERROR_SUCCESS)
    {

        if(ha->dwFlags & MPQ_FLAG_READ_ONLY)
            nError = ERROR_ACCESS_DENIED;


        if(IsPseudoFileName(szFileName, NULL) || IsPseudoFileName(szNewFileName, NULL))
            nError = ERROR_INVALID_PARAMETER;


        if(IsInternalMpqFileName(szFileName) || IsInternalMpqFileName(szNewFileName))
            nError = ERROR_INTERNAL_FILE;
    }


    if(nError == ERROR_SUCCESS)
    {

        pFileEntry = GetFileEntryLocale(ha, szFileName, lcFileLocale);
        if(pFileEntry == NULL)
            nError = ERROR_FILE_NOT_FOUND;
    }


    if(nError == ERROR_SUCCESS)
    {
        if(GetFileEntryLocale(ha, szNewFileName, pFileEntry->lcLocale) != NULL)
            nError = ERROR_ALREADY_EXISTS;
    }


    if(nError == ERROR_SUCCESS)
    {

        nError = RenameFileEntry(ha, pFileEntry, szNewFileName);
    }


    if(nError == ERROR_SUCCESS)
    {


        if(pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED)
        {
            hf = CreateMpqFile(ha);
            if(hf != NULL)
            {

                hf->pFileEntry = pFileEntry;
                hf->dwDataSize = pFileEntry->dwFileSize;
                nError = RecryptFileData(ha, hf, szFileName, szNewFileName);


                if(ha->pHeader->dwRawChunkSize != 0)
                {
                    RawDataOffs = ha->MpqPos + pFileEntry->ByteOffset;
                    WriteMpqDataMD5(ha->pStream,
                                    RawDataOffs,
                                    pFileEntry->dwCmpSize,
                                    ha->pHeader->dwRawChunkSize);
                }

                FreeMPQFile(hf);
            }
            else
            {
                nError = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
    }


    if(nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}
