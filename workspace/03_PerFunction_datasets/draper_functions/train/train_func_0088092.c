Oct6100ApiAssertToneDetectionParams(
				IN OUT	tPOCT6100_INSTANCE_API					f_pApiInstance,
				IN		tPOCT6100_TONE_DETECTION_DISABLE		f_pToneDetectDisable,
				OUT		PUINT32									f_pulChannelIndex,
				OUT		PUINT32									f_pulToneEventNumber,
				OUT		PUINT32									f_pulExtToneChanIndex,

				OUT		PBOOL									f_pfDisableAll )
{
	tPOCT6100_API_CHANNEL		pEchoChannel;
	UINT32	ulEntryOpenCnt;
	UINT32	i;


	if ( (f_pToneDetectDisable->ulChannelHndl & cOCT6100_HNDL_TAG_MASK) != cOCT6100_HNDL_TAG_CHANNEL )
		return cOCT6100_ERR_TONE_DETECTION_CHANNEL_HANDLE_INVALID;

	*f_pulChannelIndex = f_pToneDetectDisable->ulChannelHndl & cOCT6100_HNDL_INDEX_MASK;
	if ( *f_pulChannelIndex >= f_pApiInstance->pSharedInfo->ChipConfig.usMaxChannels )
		return cOCT6100_ERR_TONE_DETECTION_CHANNEL_HANDLE_INVALID;

	mOCT6100_GET_CHANNEL_ENTRY_PNT( f_pApiInstance->pSharedInfo, pEchoChannel, *f_pulChannelIndex )


	ulEntryOpenCnt = (f_pToneDetectDisable->ulChannelHndl >> cOCT6100_ENTRY_OPEN_CNT_SHIFT) & cOCT6100_ENTRY_OPEN_CNT_MASK;


	if ( pEchoChannel->fReserved != TRUE )
		return cOCT6100_ERR_TONE_DETECTION_CHANNEL_NOT_OPEN;
	if ( ulEntryOpenCnt != pEchoChannel->byEntryOpenCnt )
		return cOCT6100_ERR_TONE_DETECTION_CHANNEL_HANDLE_INVALID;


	*f_pulExtToneChanIndex = pEchoChannel->usExtToneChanIndex;


	if ( f_pToneDetectDisable->fDisableAll != TRUE && f_pToneDetectDisable->fDisableAll != FALSE )
		return cOCT6100_ERR_TONE_DETECTION_DISABLE_ALL;


	if ( f_pToneDetectDisable->fDisableAll == FALSE )
	{
		for ( i = 0; i < cOCT6100_MAX_TONE_EVENT; i++ )
		{
			if ( f_pApiInstance->pSharedInfo->ImageInfo.aToneInfo[ i ].ulToneID == f_pToneDetectDisable->ulToneNumber )
			{
				*f_pulToneEventNumber = i;
				break;
			}
		}


		if ( i == cOCT6100_MAX_TONE_EVENT )
			return cOCT6100_ERR_NOT_SUPPORTED_TONE_NOT_PRESENT_IN_FIRMWARE;


		if ((( pEchoChannel->aulToneConf[ *f_pulToneEventNumber / 32 ] >> ( 31 - ( *f_pulToneEventNumber % 32 ))) & 0x1) == 0 )
			return cOCT6100_ERR_TONE_DETECTION_TONE_NOT_ACTIVATED;
	}


	*f_pfDisableAll = f_pToneDetectDisable->fDisableAll;

	return cOCT6100_ERR_OK;
}
