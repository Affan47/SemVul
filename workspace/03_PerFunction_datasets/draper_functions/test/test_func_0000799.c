GetFirstHashEntry(TMPQArchive * ha, const char * szFileName)
{
    TMPQHash * pStartHash;
    TMPQHash * pHashEnd = ha->pHashTable + ha->pHeader->dwHashTableSize;
    TMPQHash * pHash;
    DWORD dwHashTableSizeMask;
    DWORD dwIndex = HashString(szFileName, MPQ_HASH_TABLE_INDEX);
    DWORD dwName1 = HashString(szFileName, MPQ_HASH_NAME_A);
    DWORD dwName2 = HashString(szFileName, MPQ_HASH_NAME_B);


    dwHashTableSizeMask = ha->pHeader->dwHashTableSize ? (ha->pHeader->dwHashTableSize - 1) : 0;
    pStartHash = pHash = ha->pHashTable + (dwIndex & dwHashTableSizeMask);


    while(pHash->dwBlockIndex != HASH_ENTRY_FREE)
    {

        if(pHash->dwName1 == dwName1 && pHash->dwName2 == dwName2 && pHash->dwBlockIndex < ha->dwFileTableSize)
            return pHash;


        if(++pHash >= pHashEnd)
            pHash = ha->pHashTable;
        if(pHash == pStartHash)
            break;
    }


    return NULL;
}
