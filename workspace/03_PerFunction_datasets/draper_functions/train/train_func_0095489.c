Oct6100ApiUpdateIntrptStates(
				IN OUT	tPOCT6100_INSTANCE_API			f_pApiInstance,
				IN		tPOCT6100_INTERRUPT_FLAGS		f_pIntFlags )
{
	tPOCT6100_API_INTRPT_CONFIG	pIntrptConfig;
	tPOCT6100_API_INTRPT_MANAGE	pIntrptManage;

	pIntrptConfig = &f_pApiInstance->pSharedInfo->IntrptConfig;
	pIntrptManage = &f_pApiInstance->pSharedInfo->IntrptManage;


	if ( ( f_pIntFlags->fFatalReadTimeout == TRUE) &&
		 pIntrptConfig->byFatalMemoryConfig == cOCT6100_INTERRUPT_TIMEOUT &&
		 pIntrptManage->byFatalMemoryState == cOCT6100_INTRPT_ACTIVE )
	{
		pIntrptManage->byFatalMemoryState = cOCT6100_INTRPT_WILL_TIMEOUT;
		pIntrptManage->ulFatalMemoryDisableMclkHigh = pIntrptManage->ulRegMclkTimeHigh;
		pIntrptManage->ulFatalMemoryDisableMclkLow = pIntrptManage->ulRegMclkTimeLow;
	}

	if ( (f_pIntFlags->fErrorRefreshTooLate == TRUE ||
		  f_pIntFlags->fErrorPllJitter == TRUE ) &&
		 pIntrptConfig->byErrorMemoryConfig == cOCT6100_INTERRUPT_TIMEOUT &&
		 pIntrptManage->byErrorMemoryState == cOCT6100_INTRPT_ACTIVE )
	{
		pIntrptManage->byErrorMemoryState = cOCT6100_INTRPT_WILL_TIMEOUT;
		pIntrptManage->ulErrorMemoryDisableMclkHigh = pIntrptManage->ulRegMclkTimeHigh;
		pIntrptManage->ulErrorMemoryDisableMclkLow = pIntrptManage->ulRegMclkTimeLow;
	}

	if ( (f_pIntFlags->fErrorOverflowToneEvents == TRUE) &&
		 pIntrptConfig->byErrorOverflowToneEventsConfig == cOCT6100_INTERRUPT_TIMEOUT &&
		 pIntrptManage->byErrorOverflowToneEventsState == cOCT6100_INTRPT_ACTIVE )
	{
		pIntrptManage->byErrorOverflowToneEventsState = cOCT6100_INTRPT_WILL_TIMEOUT;
		pIntrptManage->ulErrorOverflowToneEventsDisableMclkHigh = pIntrptManage->ulRegMclkTimeHigh;
		pIntrptManage->ulErrorOverflowToneEventsDisableMclkLow = pIntrptManage->ulRegMclkTimeLow;
	}

	if ( (f_pIntFlags->fErrorH100OutOfSync == TRUE ||
		  f_pIntFlags->fErrorH100ClkA == TRUE ||
		  f_pIntFlags->fErrorH100ClkB == TRUE ||
		  f_pIntFlags->fErrorH100FrameA == TRUE ) &&
		 pIntrptConfig->byErrorH100Config == cOCT6100_INTERRUPT_TIMEOUT &&
		 pIntrptManage->byErrorH100State == cOCT6100_INTRPT_ACTIVE )
	{
		pIntrptManage->byErrorH100State = cOCT6100_INTRPT_WILL_TIMEOUT;
		pIntrptManage->ulErrorH100DisableMclkHigh = pIntrptManage->ulRegMclkTimeHigh;
		pIntrptManage->ulErrorH100DisableMclkLow = pIntrptManage->ulRegMclkTimeLow;
	}


	return cOCT6100_ERR_OK;
}
