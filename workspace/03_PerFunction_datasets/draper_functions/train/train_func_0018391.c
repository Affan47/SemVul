Oct6100BufferPlayoutTransferEvents(
				IN OUT	tPOCT6100_INSTANCE_API			f_pApiInstance,
				IN		UINT32							f_ulResetBuf )
{
	tPOCT6100_SHARED_INFO				pSharedInfo;
	tPOCT6100_API_CHANNEL				pEchoChannel;

	UINT32	ulChannelIndex;
	UINT32	ulResult;
	UINT32	ulLastBufPlayoutEventBufferOverflowCnt;


	pSharedInfo = f_pApiInstance->pSharedInfo;


	if ( f_ulResetBuf == TRUE )
	{
		pSharedInfo->SoftBufs.ulBufPlayoutEventBufferOverflowCnt = 0;


		return cOCT6100_ERR_OK;
	}


	if ( pSharedInfo->ChipStats.usNumberActiveBufPlayoutPorts == 0 )
	{


		return cOCT6100_ERR_OK;
	}


	ulLastBufPlayoutEventBufferOverflowCnt = pSharedInfo->SoftBufs.ulBufPlayoutEventBufferOverflowCnt;


	for ( ulChannelIndex = 0; ulChannelIndex < pSharedInfo->ChipConfig.usMaxChannels; ulChannelIndex++ )
	{
		mOCT6100_GET_CHANNEL_ENTRY_PNT( pSharedInfo, pEchoChannel, ulChannelIndex );


		if ( pEchoChannel->fBufPlayoutActive == TRUE )
		{

			if ( ulLastBufPlayoutEventBufferOverflowCnt == pSharedInfo->SoftBufs.ulBufPlayoutEventBufferOverflowCnt )
			{

				if ( ( pEchoChannel->fRinBufPlayoutNotifyOnStop == TRUE )
					&& ( pEchoChannel->fRinBufPlaying == TRUE ) )
				{
					ulResult = Oct6100BufferPlayoutCheckForSpecificEvent( f_pApiInstance, ulChannelIndex, cOCT6100_CHANNEL_PORT_ROUT, TRUE, NULL );
					if ( ulResult != cOCT6100_ERR_OK )
						return ulResult;
				}
			}
			else
			{

				break;
			}


			if ( ulLastBufPlayoutEventBufferOverflowCnt == pSharedInfo->SoftBufs.ulBufPlayoutEventBufferOverflowCnt )
			{

				if ( ( pEchoChannel->fSoutBufPlayoutNotifyOnStop == TRUE )
					&& ( pEchoChannel->fSoutBufPlaying == TRUE ) )
				{
					ulResult = Oct6100BufferPlayoutCheckForSpecificEvent( f_pApiInstance, ulChannelIndex, cOCT6100_CHANNEL_PORT_SOUT, TRUE, NULL );
					if ( ulResult != cOCT6100_ERR_OK )
						return ulResult;
				}
			}
			else
			{

				break;
			}
		}
	}

	return cOCT6100_ERR_OK;
}
