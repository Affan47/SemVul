DoLoad(void * p)
{
	static unsigned uLedBitsOld=0;
#if HAVE_GETLOADAVG
    double                dLoadLastMin;
#else
#ifdef __linux__
	char					acLoadAvg[256];
	unsigned			uLoadLastMinInt;
	unsigned			uLoadLastMinDec;
#else
#error "No input method found for LOAD"
#endif
#endif
	unsigned 			uLoad;
	unsigned 			uLedBits;


#if HAVE_GETLOADAVG
	getloadavg(&dLoadLastMin, 1);
    uLoad=(unsigned)(dLoadLastMin*100/15);
#else
#ifdef __linux__
	if (0 == GetInFile ("/proc/loadavg",acLoadAvg,sizeof(acLoadAvg)))
		return;

	if (2 != sscanf(acLoadAvg,"%u.%u ",&uLoadLastMinInt, &uLoadLastMinDec))
		return;

	uLoad=(unsigned)((uLoadLastMinInt*100+uLoadLastMinDec)/15);
#else
#error "No input method found for LOAD"
#endif
#endif
	uLoad=(uLoad >= 128) ? 256 : uLoad<<1;

	for (uLedBits=1;uLoad>1;uLedBits=uLedBits<<1)
		uLoad=uLoad>>1;


	if (uStackStyle & STACK_LINE)
		uLedBits>>=1;
	if (uStackStyle & STACK_BAR || uStackStyle & STACK_RAW)
		uLedBits--;
	if (uStackStyle & STACK_REVERSE)
		uLedBits^=0xFF;


	if (uLedBits != uLedBitsOld)
	{
		uLedBitsOld=uLedBits;
		DrvSetLeds(LED_LOAD_LO-1+uLedBits);
	}
}
