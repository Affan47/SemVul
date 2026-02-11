Oct6100ChannelModify(
				IN tPOCT6100_INSTANCE_API		f_pApiInstance,
				IN OUT tPOCT6100_CHANNEL_MODIFY	f_pChannelModify )
{
	tOCT6100_SEIZE_SERIALIZE_OBJECT		SeizeSerObj;
	tOCT6100_RELEASE_SERIALIZE_OBJECT	ReleaseSerObj;
	UINT32								ulSerRes = cOCT6100_ERR_OK;
	UINT32								ulFncRes = cOCT6100_ERR_OK;


	SeizeSerObj.pProcessContext = f_pApiInstance->pProcessContext;
	ReleaseSerObj.pProcessContext = f_pApiInstance->pProcessContext;


	SeizeSerObj.ulSerialObjHndl = f_pApiInstance->ulApiSerObj;
	SeizeSerObj.ulTryTimeMs = cOCT6100_WAIT_INFINITELY;
	ulSerRes = Oct6100UserSeizeSerializeObject( &SeizeSerObj );
	if ( ulSerRes == cOCT6100_ERR_OK )
	{

		if ( f_pChannelModify->fApplyToAllChannels != TRUE &&
			f_pChannelModify->fApplyToAllChannels != FALSE )
			return cOCT6100_ERR_CHANNEL_APPLY_TO_ALL_CHANNELS;


		if ( f_pChannelModify->fApplyToAllChannels == TRUE )
		{
			tPOCT6100_API_CHANNEL	pChanEntry;
			UINT16					usChanIndex;


			for ( usChanIndex = 0; usChanIndex < f_pApiInstance->pSharedInfo->ChipConfig.usMaxChannels; usChanIndex++ )
			{
				mOCT6100_GET_CHANNEL_ENTRY_PNT( f_pApiInstance->pSharedInfo, pChanEntry, usChanIndex );


				if ( pChanEntry->fReserved == TRUE )
				{

					f_pChannelModify->ulChannelHndl = cOCT6100_HNDL_TAG_CHANNEL | ( pChanEntry->byEntryOpenCnt << cOCT6100_ENTRY_OPEN_CNT_SHIFT ) | usChanIndex;


					ulFncRes = Oct6100ChannelModifySer( f_pApiInstance, f_pChannelModify );
					if ( ulFncRes != cOCT6100_ERR_OK )
						break;
				}
			}
		}
		else
		{

			ulFncRes = Oct6100ChannelModifySer( f_pApiInstance, f_pChannelModify );
		}
	}
	else
	{
		return ulSerRes;
	}


	ReleaseSerObj.ulSerialObjHndl = f_pApiInstance->ulApiSerObj;
	ulSerRes = Oct6100UserReleaseSerializeObject( &ReleaseSerObj );


	if ( ulSerRes != cOCT6100_ERR_OK )
		return ulSerRes;
	if ( ulFncRes != cOCT6100_ERR_OK )
		return ulFncRes;

	return cOCT6100_ERR_OK;
}
