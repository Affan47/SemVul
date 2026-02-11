Oct6100ApiReleaseTsst(
				IN OUT	tPOCT6100_INSTANCE_API		f_pApiInstance,
				IN		UINT32						f_ulTimeslot,
				IN		UINT32						f_ulStream,
				IN		UINT32						f_ulNumTsst,
				IN		UINT32						f_ulDirection,
				IN		UINT16						f_usTsstListIndex)
{
	tPOCT6100_SHARED_INFO	pSharedInfo;
	PUINT32	pulTsstAlloc;
	PVOID	pTsstListAlloc;
	UINT32	ulResult;
	UINT32	ulStream;
	UINT32	ulTimeslot;


	pSharedInfo = f_pApiInstance->pSharedInfo;

	if ( f_usTsstListIndex != cOCT6100_INVALID_INDEX )
	{
		mOCT6100_GET_TSST_LIST_ALLOC_PNT( pSharedInfo, pTsstListAlloc )

		ulResult = OctapiLlmAllocDealloc( pTsstListAlloc, f_usTsstListIndex );
		if ( ulResult != cOCT6100_ERR_OK )
		{
			return cOCT6100_ERR_FATAL_53;
		}
	}

	mOCT6100_GET_TSST_ALLOC_PNT( f_pApiInstance->pSharedInfo, pulTsstAlloc );


	ulStream	= f_ulStream;
	ulTimeslot	= f_ulTimeslot;


	if ( pSharedInfo->ChipConfig.aulTdmStreamFreqs[ f_ulStream / 4 ] == cOCT6100_TDM_STREAM_FREQ_16MHZ )
	{
		if ( f_ulDirection == cOCT6100_INPUT_TSST )
		{
			ulStream	= f_ulStream + ( f_ulTimeslot % 2 ) * 16;
			ulTimeslot	= f_ulTimeslot / 2;
		}
		else
		{
			ulStream	= ( f_ulStream - 16 ) + ( f_ulTimeslot % 2 ) * 16;

			if ( f_ulStream < 28 && ((f_ulTimeslot % 2) == 1) )
			{
				ulTimeslot	= ((f_ulTimeslot / 2) + 4) % 128;
			}
			else
			{
				ulTimeslot	= f_ulTimeslot / 2 ;
			}
		}
	}


	switch ( pSharedInfo->ChipConfig.aulTdmStreamFreqs[ ulStream / 4 ] )
	{
	case cOCT6100_TDM_STREAM_FREQ_2MHZ:
		ulTimeslot *= 4;
		break;
	case cOCT6100_TDM_STREAM_FREQ_4MHZ:
		ulTimeslot *= 2;
		break;
	case cOCT6100_TDM_STREAM_FREQ_8MHZ:
		ulTimeslot *= 1;
		break;
	case cOCT6100_TDM_STREAM_FREQ_16MHZ:
		ulTimeslot *= 1;
		break;
	default:
		return cOCT6100_ERR_FATAL_DE;
	}


	if ( ((pulTsstAlloc[ ulTimeslot ] >> ulStream) & 0x1) != 0x1 )
		return cOCT6100_ERR_FATAL_55;


	pulTsstAlloc[ ulTimeslot ] &= ~(0x1 << ulStream);


	if ( f_ulNumTsst == 2 )
	{

		if ( ((pulTsstAlloc[ ulTimeslot ] >> ( ulStream - 1)) & 0x1) != 0x1 )
			return cOCT6100_ERR_FATAL_54;


		pulTsstAlloc[ ulTimeslot ] &= ~(0x1 << (ulStream - 1));

	}

	return cOCT6100_ERR_OK;
}
