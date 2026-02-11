strutou64(str)
	CONST char *str;
{
	char *p = (char *) str;
	u_signed64 u64 = 0;

	while (isspace (*p)) p++;
	while (*p) {
		if (! isdigit (*p)) break;
			u64 = u64 * 10 + (*p++ - '0');
	}
	if (*p && ! *(p + 1))
		if (*p == 'k') u64 *= ONE_KB;
		else if (*p == 'M') u64 *= ONE_MB;
		else if (*p == 'G') u64 *= ONE_GB;
		else if (*p == 'T') u64 *= ONE_TB;
		else if (*p == 'P') u64 *= ONE_PB;
	return (u64);
}
