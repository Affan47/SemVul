InitWriteHeader()
{
    int i;

    if (m_eAccessMode != TABWrite || m_bWriteHeaderInitialized)
        return 0;


    m_nFirstRecordPtr = (m_numFields+1)*32 + 1;

    m_nRecordSize = 1;
    for(i=0; i<m_numFields; i++)
    {
        m_nRecordSize += m_pasFieldDef[i].byLength;
    }


    m_nBlockSize = m_nRecordSize;

    CPLAssert( m_poRecordBlock == NULL );
    m_poRecordBlock = new TABRawBinBlock(m_eAccessMode, FALSE);
    m_poRecordBlock->InitNewBlock(m_fp, m_nBlockSize);
    m_poRecordBlock->SetFirstBlockPtr(m_nFirstRecordPtr);


    m_bWriteHeaderInitialized = TRUE;

    return 0;
}
