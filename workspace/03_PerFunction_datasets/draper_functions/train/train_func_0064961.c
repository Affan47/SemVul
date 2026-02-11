GetRecordBlock(int nRecordId)
{
    m_bCurRecordDeletedFlag = FALSE;

    if (m_eAccessMode == TABRead)
    {


        int nFileOffset;

        nFileOffset = m_nFirstRecordPtr+(nRecordId-1)*m_nRecordSize;


        if ( m_poRecordBlock == NULL ||
             nRecordId < 1 || nRecordId > m_numRecords ||
             m_poRecordBlock->GotoByteInFile(nFileOffset) != 0 )
        {
            CPLError(CE_Failure, CPLE_FileIO,
                     "Failed reading .DAT record block for record #%d in %s",
                     nRecordId, m_pszFname);
            return NULL;
        }


        if (m_poRecordBlock->ReadByte() != ' ')
        {
            m_bCurRecordDeletedFlag = TRUE;
        }
    }
    else if (m_eAccessMode == TABWrite && nRecordId > 0)
    {


        int nFileOffset;


        if (!m_bWriteHeaderInitialized)
        {
            WriteHeader();
        }

        m_numRecords = MAX(nRecordId, m_numRecords);

        nFileOffset = m_nFirstRecordPtr+(nRecordId-1)*m_nRecordSize;

        m_poRecordBlock->InitNewBlock(m_fp, m_nRecordSize, nFileOffset);


        m_poRecordBlock->WriteByte(' ');

    }

    m_nCurRecordId = nRecordId;

    return m_poRecordBlock;
}
