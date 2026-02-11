logWrappedKey(
	FLMUINT		uiTransID,
	FLMBYTE *	pucDBKey,
	FLMUINT32	ui32DBKeyLen)
{
	RCODE			rc = FERR_OK;
	FLMBYTE *	pucPacketBody;
	FLMUINT		uiPacketBodyLen;


	if (m_bLoggingOff)
	{
		goto Exit;
	}


	flmAssert( !m_bLoggingUnknown);

	if (RC_BAD( rc = setupTransaction()))
	{
		goto Exit;
	}

	uiPacketBodyLen = 6 + ui32DBKeyLen;


	if (!haveBuffSpace( uiPacketBodyLen + RFL_PACKET_OVERHEAD))
	{
		if (RC_BAD( rc = flush( m_pCurrentBuf)))
		{
			goto Exit;
		}
	}


	pucPacketBody = getPacketBodyPtr();


	UD2FBA( (FLMUINT32) uiTransID, pucPacketBody);
	pucPacketBody += 4;


	flmAssert( ui32DBKeyLen <= 0xFFFF);
	UW2FBA( (FLMUINT16) ui32DBKeyLen, pucPacketBody);
	pucPacketBody += 2;


	if (ui32DBKeyLen)
	{
		f_memcpy( pucPacketBody, pucDBKey, ui32DBKeyLen);
		pucPacketBody += ui32DBKeyLen;
	}


	if (RC_BAD( rc = finishPacket( RFL_WRAP_KEY_PACKET, uiPacketBodyLen, TRUE)))
	{
		goto Exit;
	}

	finalizeTransaction();

Exit:

	return (rc);
}
