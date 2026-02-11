CopyData (const BYTE *pBuffer, DWORD iCount)
{
    if (m_iCurPclBufferPos + (int) iCount < m_iPclBufferSize)
    {
        memcpy (m_pbyPclBuffer + m_iCurPclBufferPos, pBuffer, iCount);
        m_iCurPclBufferPos += iCount;
       return 0;
    }
    BYTE    *p = new BYTE[m_iPclBufferSize + BUFFER_CHUNK_SIZE + 2];
    if (p == NULL)
    {
        m_bSpeedMechEnabled = FALSE;
	return 1;
    }
    memcpy (p, m_pbyPclBuffer, m_iCurPclBufferPos);
    delete [] m_pbyPclBuffer;
    m_pbyPclBuffer = p;
    memcpy (m_pbyPclBuffer + m_iCurPclBufferPos, pBuffer, iCount);
    m_iCurPclBufferPos += iCount;
    m_iPclBufferSize += BUFFER_CHUNK_SIZE;
    return 0;
}
