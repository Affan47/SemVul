logReduce(
	FLMUINT	uiTransID,
	FLMUINT	uiCount)
{
	RCODE			rc = FERR_OK;
	FLMBYTE *	pucPacketBody;
	FLMUINT		uiPacketBodyLen;


	if (m_pFile->FileHdr.uiVersionNum < FLM_FILE_FORMAT_VER_4_3)
	{
		goto Exit;
	}


	if (m_bLoggingOff)
	{
		goto Exit;
	}


	flmAssert( !m_bLoggingUnknown);


	if (RC_BAD( rc = setupTransaction()))
	{
		goto Exit;
	}

	uiPacketBodyLen = 8;


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


	UD2FBA( (FLMUINT32) uiCount, pucPacketBody);
	pucPacketBody += 4;


	if (RC_BAD( rc = finishPacket( RFL_REDUCE_PACKET, uiPacketBodyLen, TRUE)))
	{
		goto Exit;
	}


	finalizeTransaction();

Exit:

	return (rc);
}
