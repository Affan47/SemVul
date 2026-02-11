Oct6100ApiGetChipRevisionNum(
				IN OUT	tPOCT6100_INSTANCE_API	f_pApiInstance )
{
	tPOCT6100_SHARED_INFO	pSharedInfo;
	tOCT6100_READ_PARAMS	ReadParams;
	UINT32					ulResult;
	UINT16					usReadData;


	pSharedInfo = f_pApiInstance->pSharedInfo;


	ReadParams.pProcessContext = f_pApiInstance->pProcessContext;

	ReadParams.ulUserChipId = f_pApiInstance->pSharedInfo->ChipConfig.ulUserChipId;
	ReadParams.ulReadAddress = cOCT6100_CHIP_ID_REVISION_REG;
	ReadParams.pusReadData = &usReadData;

	mOCT6100_DRIVER_READ_API( ReadParams, ulResult )
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;


	pSharedInfo->MiscVars.usChipId = (UINT16)( usReadData & 0xFF );
	pSharedInfo->MiscVars.usChipRevision = (UINT16)( usReadData >> 8 );

	return cOCT6100_ERR_OK;
}
