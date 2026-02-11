WriteBytes(int nBytesToWrite, GByte *pabySrcBuf)
{


    if (m_pabyBuf == NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "WriteBytes(): Block has not been initialized.");
        return -1;
    }

    if (m_eAccess != TABWrite && m_eAccess != TABReadWrite )
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "WriteBytes(): Block does not support write operations.");
        return -1;
    }

    if (m_nCurPos + nBytesToWrite > m_nBlockSize)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "WriteBytes(): Attempt to write past end of data block.");
        return -1;
    }


    if (pabySrcBuf)
    {
        memcpy(m_pabyBuf + m_nCurPos, pabySrcBuf, nBytesToWrite);
    }

    m_nCurPos += nBytesToWrite;

    m_nSizeUsed = MAX(m_nSizeUsed, m_nCurPos);

    m_bModified = TRUE;

    return 0;
}
