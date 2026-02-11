ReadMpqFilePatchFile(TMPQFile * hf, void * pvBuffer, DWORD dwToRead, LPDWORD pdwBytesRead)
{
    DWORD dwBytesToRead = dwToRead;
    DWORD dwBytesRead = 0;
    int nError = ERROR_SUCCESS;


    if(hf->pbFileData == NULL)
    {

        hf->pbFileData = ALLOCMEM(BYTE, hf->pFileEntry->dwFileSize);
        hf->cbFileData = hf->pFileEntry->dwFileSize;
        if(hf->pbFileData == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;


        if(hf->pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT)
            nError = ReadMpqFileSingleUnit(hf, hf->pbFileData, hf->cbFileData, &dwBytesRead);
        else
            nError = ReadMpqFile(hf, hf->pbFileData, hf->cbFileData, &dwBytesRead);


        if(nError == ERROR_SUCCESS && dwBytesRead != hf->cbFileData)
            nError = ERROR_FILE_CORRUPT;


        if(nError == ERROR_SUCCESS)
            nError = PatchFileData(hf);


        hf->dwFilePos = 0;
        dwBytesRead = 0;
    }


    if(nError == ERROR_SUCCESS)
    {
        if(hf->dwFilePos < hf->cbFileData)
        {

            if((hf->dwFilePos + dwToRead) > hf->cbFileData)
                dwToRead = hf->cbFileData - hf->dwFilePos;


            memcpy(pvBuffer, hf->pbFileData + hf->dwFilePos, dwToRead);
            hf->dwFilePos += dwToRead;
            dwBytesRead = dwToRead;
        }


        nError = (dwBytesRead == dwBytesToRead) ? ERROR_SUCCESS : ERROR_HANDLE_EOF;
    }


    if(pdwBytesRead != NULL)
        *pdwBytesRead = dwBytesRead;
    return nError;
}
