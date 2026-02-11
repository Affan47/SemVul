Oct6100ApiRand(
				IN		UINT32				f_ulRange )
{
	static UINT32	ulRandomSeed = 0x12345678;
	UINT32			ulBit0;

	UINT32			i, j;
	UINT16			ulWithinRange = FALSE;

	UINT32			ulResult = cOCT6100_ERR_OK;
	UINT16			ulLoop;

	UINT32			ulRangeMask;
	UINT32			ulAddedValue;


	ulRangeMask = 1;
	ulLoop = TRUE;
	i = 1;

	while ( ulLoop )
	{

		ulAddedValue = 2;
		for ( j = 1; j < i; j++ )
			ulAddedValue *= 2;

		ulRangeMask = ulRangeMask + ulAddedValue;

		if ( ulRangeMask >= f_ulRange )
			ulLoop = FALSE;

		i++;
	}

	while ( !ulWithinRange )
	{
		ulBit0 = ((ulRandomSeed >> 19) & 0x1) ^ ((ulRandomSeed >> 16) & 0x1);
		ulRandomSeed = ((ulRandomSeed << 1) & 0xFFFFF) | ulBit0;

		ulResult = ulRandomSeed & ulRangeMask;

		if ( ulResult <= f_ulRange )
			ulWithinRange = TRUE;
	}

	return ulResult;
}
