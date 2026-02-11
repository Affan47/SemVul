format_ie(const char *ie)
{
	static char result[3 * MAX_FMT_IE_LEN];
	int len, count;
	char *pout = result;

	if (!ie)
		return "NULL";

	count = len = ie[0];
	if (count > MAX_FMT_IE_LEN)
		count = MAX_FMT_IE_LEN - 1;
	while (count--) {
		*pout++ = hex_asc_hi(*++ie);
		*pout++ = hex_asc_lo(*ie);
		*pout++ = ' ';
	}
	if (len > MAX_FMT_IE_LEN) {
		*pout++ = '.';
		*pout++ = '.';
		*pout++ = '.';
	}
	*--pout = 0;
	return result;
}
