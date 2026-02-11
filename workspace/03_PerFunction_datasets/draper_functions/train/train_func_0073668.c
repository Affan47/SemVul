fsvGetStreamedResponse(
	FSV_SESN *		pSession,
	FLMBYTE *		pucPacketBuffer,
	FLMUINT			uiMaxPacketSize,
	FLMUINT *		puiPacketSize,
	FLMBOOL *		pbLastPacket)
{
	FCS_BIOS *		pServerBOStream = NULL;
	RCODE				rc = FERR_OK;

	if (RC_BAD( rc = pSession->GetBOStream( &pServerBOStream)))
	{
		goto Exit;
	}

	if (RC_BAD( rc = pServerBOStream->read( pucPacketBuffer, uiMaxPacketSize,
				  puiPacketSize)))
	{
		if (rc == FERR_EOF_HIT)
		{
			*pbLastPacket = TRUE;
			rc = FERR_OK;
		}

		goto Exit;
	}

	if (!pServerBOStream->isDataAvailable())
	{
		*pbLastPacket = TRUE;
	}

Exit:

	return (rc);
}
