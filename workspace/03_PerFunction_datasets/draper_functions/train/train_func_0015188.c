logData(
	FLMUINT				uiDataLen,
	const FLMBYTE *	pucData,
	FLMUINT				uiPacketType,
	FLMUINT *			puiPacketLenRV,
	FLMUINT *			puiPacketCountRV,
	FLMUINT *			puiMaxLogBytesNeededRV,
	FLMUINT *			puiTotalBytesLoggedRV)
{
	RCODE			rc = FERR_OK;
	FLMUINT		uiBytesAvail;
	FLMBYTE *	pucDest;

	while (uiDataLen)
	{
		if (RC_BAD( rc = makeRoom( uiDataLen, puiPacketLenRV, uiPacketType,
					  &uiBytesAvail, puiPacketCountRV)))
		{
			goto Exit;
		}

		if (uiBytesAvail)
		{
			if (puiMaxLogBytesNeededRV)
			{
				if (RC_BAD( rc = RflCheckMaxLogged( puiMaxLogBytesNeededRV,
							  *puiPacketCountRV, puiTotalBytesLoggedRV, uiBytesAvail)))
				{
					goto Exit;
				}
			}

			pucDest = getPacketPtr() + (*puiPacketLenRV);
			f_memcpy( pucDest, pucData, uiBytesAvail);
			uiDataLen -= uiBytesAvail;
			pucData += uiBytesAvail;
			(*puiPacketLenRV) += uiBytesAvail;
		}


		if (uiDataLen)
		{
			if (puiPacketCountRV)
			{
				(*puiPacketCountRV)++;
			}

			if (RC_BAD( rc = finishPacket( uiPacketType,
						  *puiPacketLenRV - RFL_PACKET_OVERHEAD, FALSE)))
			{
				goto Exit;
			}

			if (RC_BAD( rc = flush( m_pCurrentBuf)))
			{
				goto Exit;
			}

			*puiPacketLenRV = RFL_PACKET_OVERHEAD;
			if (puiMaxLogBytesNeededRV)
			{
				if (RC_BAD( rc = RflCheckMaxLogged( puiMaxLogBytesNeededRV,
							  *puiPacketCountRV, puiTotalBytesLoggedRV,
							  RFL_PACKET_OVERHEAD)))
				{
					goto Exit;
				}
			}
		}
	}

Exit:

	return (rc);
}
