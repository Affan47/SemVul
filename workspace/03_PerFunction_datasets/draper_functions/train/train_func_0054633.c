GetFileEntryExact(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pHash;
    DWORD dwFileIndex;


    if(ha->pHetTable != NULL)
    {
        dwFileIndex = GetFileIndex_Het(ha, szFileName);
        if(dwFileIndex != HASH_ENTRY_FREE)
            return ha->pFileTable + dwFileIndex;
    }


    if(ha->pHashTable != NULL)
    {
        pHash = GetHashEntryExact(ha, szFileName, lcLocale);
        if(pHash != NULL && pHash->dwBlockIndex < ha->dwFileTableSize)
            return ha->pFileTable + pHash->dwBlockIndex;
    }


    return NULL;
}
