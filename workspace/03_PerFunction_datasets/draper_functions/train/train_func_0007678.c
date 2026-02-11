WriteDateTimeField(int nYear, int nMonth, int nDay,
                                   int nHour, int nMinute, int nSecond, int nMS,
                                   TABINDFile *poINDFile, int nIndexNo)
{
    GInt32 nS = (nHour*3600+nMinute*60+nSecond)*1000+nMS;

    if (m_poRecordBlock == NULL)
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
            "Can't write field value: GetRecordBlock() has not been called.");
        return -1;
    }

    m_poRecordBlock->WriteInt16((GInt16)nYear);
    m_poRecordBlock->WriteByte((GByte)nMonth);
    m_poRecordBlock->WriteByte((GByte)nDay);
    m_poRecordBlock->WriteInt32(nS);

    if (CPLGetLastErrorNo() != 0)
        return -1;


    if (poINDFile && nIndexNo > 0)
    {


        CPLAssert(FALSE);
        GByte *pKey = poINDFile->BuildKey(nIndexNo, (nYear*0x10000 +
                                                     nMonth * 0x100 + nDay));
        if (poINDFile->AddEntry(nIndexNo, pKey, m_nCurRecordId) != 0)
            return -1;
    }

    return 0;
}
