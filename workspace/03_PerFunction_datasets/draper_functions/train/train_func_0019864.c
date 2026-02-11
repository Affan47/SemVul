Oct6100ApiGetPreviousEvent(
				IN OUT	tPOCT6100_INSTANCE_API			f_pApiInstance,
				IN		UINT16							f_usEntryIndex,
				IN		UINT16							f_usSearchedIndex,
				IN		UINT16							f_usLoopCnt,
				OUT		PUINT16							f_pusPreviousIndex )
{
	tPOCT6100_API_MIXER_EVENT	pCurrentEntry;
	UINT32	ulResult;


	mOCT6100_GET_MIXER_EVENT_ENTRY_PNT( f_pApiInstance->pSharedInfo, pCurrentEntry, f_usEntryIndex );


	if ( f_usLoopCnt == cOCT6100_MAX_MIXER_EVENTS )
		return cOCT6100_ERR_FATAL_E3;

	if ( pCurrentEntry->usNextEventPtr == cOCT6100_INVALID_INDEX )
	{

		ulResult = cOCT6100_ERR_CONF_MIXER_EVENT_NOT_FOUND;
	}
	else if ( pCurrentEntry->usNextEventPtr == f_usSearchedIndex )
	{

		*f_pusPreviousIndex = f_usEntryIndex;
		ulResult = cOCT6100_ERR_OK;
	}
	else
	{

		f_usLoopCnt++;
		ulResult = Oct6100ApiGetPreviousEvent( f_pApiInstance, pCurrentEntry->usNextEventPtr, f_usSearchedIndex, f_usLoopCnt, f_pusPreviousIndex );
	}

	return ulResult;
}
