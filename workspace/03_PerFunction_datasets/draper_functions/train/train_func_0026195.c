GetRecommendedMaxConnections()
{
#ifndef CLIENT_GUI
	int iRealMax = PlatformSpecific::GetMaxConnections();
	if(iRealMax == -1 || iRealMax > 520) {
		return 500;
	}
	if(iRealMax < 20) {
		return iRealMax;
	}
	if(iRealMax <= 256) {
		return iRealMax - 10;
	}
	return iRealMax - 20;
#else
	return 500;
#endif
}
