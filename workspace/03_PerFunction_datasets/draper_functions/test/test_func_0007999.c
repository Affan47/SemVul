GB_ReturnConstString(const char *str, int len)
{
	TEMP.type = T_CSTRING;
	TEMP._string.addr = (char *)str;
	TEMP._string.start = 0;
	TEMP._string.len = len;

	if (TEMP._string.len == 0)
		TEMP._string.addr = 0;
}
