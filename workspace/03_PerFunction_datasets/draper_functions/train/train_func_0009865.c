ReadCharField(int nWidth)
{


    if (m_bCurRecordDeletedFlag)
        return "";

    if (m_poRecordBlock == NULL)
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "Can't read field value: file is not opened.");
        return "";
    }

    if (nWidth < 1 || nWidth > 255)
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "Illegal width for a char field: %d", nWidth);
        return "";
    }

    if (m_poRecordBlock->ReadBytes(nWidth, (GByte*)m_szBuffer) != 0)
        return "";

    m_szBuffer[nWidth] = '\0';


    if (m_eTableType == TABTableDBF)
    {
        int nLen = strlen(m_szBuffer)-1;
        while(nLen>=0 && m_szBuffer[nLen] == ' ')
            m_szBuffer[nLen--] = '\0';
    }

    return m_szBuffer;
}
