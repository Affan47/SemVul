startLoggingUnknown(void)
{
	RCODE			rc = FERR_OK;
	FLMBYTE *	pucPacketBody;
	FLMUINT		uiPacketBodyLen;

	flmAssert( m_pFile);


	if (m_bLoggingOff || m_pFile->FileHdr.uiVersionNum < FLM_FILE_FORMAT_VER_4_3)
	{
		goto Exit;
	}


	flmAssert( !m_bLoggingUnknown);


	flmAssert( m_uiCurrTransID);

	m_uiOperCount++;
	uiPacketBodyLen = 4;


	if (!haveBuffSpace( uiPacketBodyLen + RFL_PACKET_OVERHEAD))
	{
		if (RC_BAD( rc = flush( m_pCurrentBuf)))
		{
			goto Exit;
		}
	}


	pucPacketBody = getPacketBodyPtr();


	UD2FBA( (FLMUINT32) m_uiCurrTransID, pucPacketBody);
	pucPacketBody += 4;


	if (RC_BAD( rc = finishPacket( RFL_START_UNKNOWN_PACKET, uiPacketBodyLen,
				  FALSE)))
	{
		goto Exit;
	}

	m_bLoggingUnknown = TRUE;
	m_uiUnknownPacketLen = RFL_PACKET_OVERHEAD;

Exit:

	return (rc);
}
