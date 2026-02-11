Oct6100ApiCpuRegisterBist(
				IN OUT	tPOCT6100_INSTANCE_API	f_pApiInstance )
{
	tPOCT6100_SHARED_INFO	pSharedInfo;
	tOCT6100_WRITE_PARAMS	WriteParams;
	tOCT6100_READ_PARAMS	ReadParams;
	UINT32	ulResult;
	UINT16	i;
	UINT16	usReadData;


	pSharedInfo = f_pApiInstance->pSharedInfo;


	WriteParams.pProcessContext = f_pApiInstance->pProcessContext;

	WriteParams.ulUserChipId = pSharedInfo->ChipConfig.ulUserChipId;

	ReadParams.pProcessContext = f_pApiInstance->pProcessContext;

	ReadParams.ulUserChipId = pSharedInfo->ChipConfig.ulUserChipId;


	ReadParams.pusReadData = &usReadData;


	for ( i = 0; i < 16; i ++ )
	{

		WriteParams.ulWriteAddress = 0x150;
		WriteParams.usWriteData = (UINT16)( 0x1 << i );

		mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;


		WriteParams.ulWriteAddress = 0x180;
		WriteParams.usWriteData = (UINT16)( 0x1 << ( 15 - i ) );

		mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;


		ReadParams.ulReadAddress = 0x150;

		mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;

		if ( usReadData != ( 0x1 << i ) )
			return cOCT6100_ERR_OPEN_CPU_REG_BIST_ERROR;

		ReadParams.ulReadAddress = 0x180;

		mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
		if ( ulResult != cOCT6100_ERR_OK )
			return ulResult;

		if ( usReadData != ( 0x1 << ( 15 - i ) ) )
			return cOCT6100_ERR_OPEN_CPU_REG_BIST_ERROR;
	}


	WriteParams.ulWriteAddress = 0x150;
	WriteParams.usWriteData = 0xCAFE;

	mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;


	WriteParams.ulWriteAddress = 0x180;
	WriteParams.usWriteData = 0xDECA;

	mOCT6100_DRIVER_WRITE_API( WriteParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;


	ReadParams.ulReadAddress = 0x150;

	mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;

	if ( usReadData != 0xCAFE )
		return cOCT6100_ERR_OPEN_CPU_REG_BIST_ERROR;

	ReadParams.ulReadAddress = 0x180;

	mOCT6100_DRIVER_READ_API( ReadParams, ulResult );
	if ( ulResult != cOCT6100_ERR_OK )
		return ulResult;

	if ( usReadData != 0xDECA )
		return cOCT6100_ERR_OPEN_CPU_REG_BIST_ERROR;

	return cOCT6100_ERR_OK;
}
