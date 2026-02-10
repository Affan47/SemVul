DoTraffic(void *p)
{

    static unsigned         uLedBitsOld=0;
	static long		            lAllPacketsPrior=0;
	static struct timeval	tWhenPrior;

    struct timeval				tWhenNow;
	struct timeval				tWhenDiff;
#if HAVE_GETIFADDRS
    struct ifaddrs              *pIfAddrs;
    struct ifaddrs              *pThisIfAddrs;
#endif
	long 					        lAllPackets=0L;
	long					        lRate;
	unsigned 					uLedBits;


	if (gettimeofday(&tWhenNow,NULL))
		return;
#if HAVE_GETIFADDRS
    if (getifaddrs(&pIfAddrs))
        return;
    for (pThisIfAddrs=pIfAddrs;pThisIfAddrs; pThisIfAddrs=pThisIfAddrs->ifa_next)
        if (pThisIfAddrs->ifa_addr && AF_MAC == pThisIfAddrs->ifa_addr->sa_family)
            if (0 == memcmp(pThisIfAddrs->ifa_name, ETHDEV "0",1+sizeof(ETHDEV)) ||
                 0 == memcmp(pThisIfAddrs->ifa_name, ETHDEV "1",1+sizeof(ETHDEV)) ||
                 0 == memcmp(pThisIfAddrs->ifa_name, ETHDEV "2",1+sizeof(ETHDEV)) ||
                 0 == memcmp(pThisIfAddrs->ifa_name, ETHDEV "3",1+sizeof(ETHDEV)))
                lAllPackets+= INOUT_PACKETS(pThisIfAddrs->ifa_data);
    freeifaddrs(pIfAddrs);
#else
#if !HAVE_GETIFADDRS && defined(__linux__)
	lAllPackets=GetPacketCount();
#else
#error "No input method found for TRAFFIC"
#endif
#endif
	if (0L == lAllPackets)
		return;
	if (0L != lAllPacketsPrior)
	{


		GetTimeDiff (&tWhenPrior, &tWhenNow, &tWhenDiff);
        if (0 == tWhenDiff.tv_sec && 0 == tWhenDiff.tv_usec)
            return;
		lRate=(lAllPackets-lAllPacketsPrior)*1000000/64/(tWhenDiff.tv_sec*1000000+tWhenDiff.tv_usec);

		if (lRate > 8192/64)
			lRate=8192/64;

		for (uLedBits=1;lRate>0;uLedBits=uLedBits<<1)
			lRate=lRate>>1;

		if (uStackStyle & STACK_LINE)
			uLedBits>>=1;
		if (uStackStyle & STACK_BAR)
			uLedBits--;
		if (uStackStyle & STACK_RAW)
			uLedBits=(lAllPackets/64)&0xFF;
		if (uStackStyle & STACK_REVERSE)
			uLedBits^=0xFF;

		if (uLedBits != uLedBitsOld)
		{
			uLedBitsOld=uLedBits;
			DrvSetLeds(LED_NO_TRAFFIC+uLedBits);
		}
	}

	lAllPacketsPrior=lAllPackets;
	tWhenPrior=tWhenNow;
}
