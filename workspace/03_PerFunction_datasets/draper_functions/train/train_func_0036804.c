Alloc(DWORD dwNewLen)
{
	if (dwNewLen > (DWORD)m_Edge)
	{

		DWORD dwNewBufferSize = (DWORD)(((dwNewLen>>16)+1)<<16);


		if (m_pBuffer == NULL) m_pBuffer = (BYTE*)malloc(dwNewBufferSize);
		else	m_pBuffer = (BYTE*)realloc(m_pBuffer, dwNewBufferSize);

		m_bFreeOnClose = true;

		m_Edge = dwNewBufferSize;
	}
	return (m_pBuffer!=0);
}
