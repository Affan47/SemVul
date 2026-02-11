tConvertDTTM(ULONG ulDTTM)
{
	struct tm	tTime;
	time_t		tResult;

	if (ulDTTM == 0) {
		return (time_t)-1;
	}
	memset(&tTime, 0, sizeof(tTime));
	tTime.tm_min = (int)(ulDTTM & 0x0000003f);
	tTime.tm_hour = (int)((ulDTTM & 0x000007c0) >> 6);
	tTime.tm_mday = (int)((ulDTTM & 0x0000f800) >> 11);
	tTime.tm_mon = (int)((ulDTTM & 0x000f0000) >> 16);
	tTime.tm_year = (int)((ulDTTM & 0x1ff00000) >> 20);
	tTime.tm_isdst = -1;
	tTime.tm_mon--;
	tResult = mktime(&tTime);
	NO_DBG_MSG(ctime(&tResult));
	return tResult;
}
