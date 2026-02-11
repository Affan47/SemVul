ReadFrom ( int iLen, int iTimeout )
{
	if ( iLen<=0 || iLen>g_iMaxPacketSize || m_iSock<0 )
		return false;

	BYTE * pBuf = m_dMinibufer;
	if ( iLen>NET_MINIBUFFER_SIZE )
	{
		if ( iLen>m_iMaxibuffer )
		{
			SafeDeleteArray ( m_pMaxibuffer );
			m_pMaxibuffer = new BYTE [ iLen ];
			m_iMaxibuffer = iLen;
		}
		pBuf = m_pMaxibuffer;
	}

	m_pCur = m_pBuf = pBuf;
	int iGot = sphSockRead ( m_iSock, pBuf, iLen, iTimeout );

	m_bError = ( iGot!=iLen );
	m_iLen = m_bError ? 0 : iLen;
	return !m_bError;
}
