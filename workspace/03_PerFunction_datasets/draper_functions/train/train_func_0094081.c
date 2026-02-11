WriteDecimalField(double dValue, int nWidth, int nPrec,
                                  TABINDFile *poINDFile, int nIndexNo)
{
    const char *pszVal;

    pszVal = CPLSPrintf("%*.*f", nWidth, nPrec, dValue);
    if ((int)strlen(pszVal) > nWidth)
        pszVal += strlen(pszVal) - nWidth;


    if (poINDFile && nIndexNo > 0)
    {
        GByte *pKey = poINDFile->BuildKey(nIndexNo, dValue);
        if (poINDFile->AddEntry(nIndexNo, pKey, m_nCurRecordId) != 0)
            return -1;
    }

    return m_poRecordBlock->WriteBytes(nWidth, (GByte*)pszVal);
}
