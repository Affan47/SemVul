TranslateHetTable(TMPQExtTable * pExtTable)
{
    HET_TABLE_HEADER HetHeader;
    TMPQHetTable * pHetTable = NULL;
    LPBYTE pbSrcData = (LPBYTE)(pExtTable + 1);


    assert(pExtTable->dwSignature == HET_TABLE_SIGNATURE);
    assert(pExtTable->dwVersion == 1);


    if(pExtTable != NULL && pExtTable->dwDataSize >= sizeof(HET_TABLE_HEADER))
    {

        memcpy(&HetHeader, pbSrcData, sizeof(HET_TABLE_HEADER));
        BSWAP_ARRAY32_UNSIGNED(&HetHeader, sizeof(HET_TABLE_HEADER));
        pbSrcData += sizeof(HET_TABLE_HEADER);


        if(HetHeader.dwTableSize == pExtTable->dwDataSize)
        {

            pHetTable = CreateHetTable(HetHeader.dwMaxFileCount, HetHeader.dwHashEntrySize, false);
            if(pHetTable != NULL)
            {

                pHetTable->dwHashTableSize  = HetHeader.dwHashTableSize;
                pHetTable->dwIndexSizeTotal = HetHeader.dwIndexSizeTotal;
                pHetTable->dwIndexSizeExtra = HetHeader.dwIndexSizeExtra;


                if(pHetTable->pHetHashes != NULL)
                    memcpy(pHetTable->pHetHashes, pbSrcData, pHetTable->dwHashTableSize);
                pbSrcData += pHetTable->dwHashTableSize;


                pHetTable->pBetIndexes = CreateBitArray(HetHeader.dwIndexTableSize * 8, 0xFF);
                if(pHetTable->pBetIndexes != NULL)
                    memcpy(pHetTable->pBetIndexes->Elements, pbSrcData, HetHeader.dwIndexTableSize);
                pbSrcData += HetHeader.dwIndexTableSize;
            }
        }
    }

    return pHetTable;
}
