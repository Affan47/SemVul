Len(long L, int type)
#endif
{
	static char buf[24];
	if (L == 1 && type != TYCHAR)
		return "";
	sprintf(buf, "[%ld]", L);
	return buf;
	}
