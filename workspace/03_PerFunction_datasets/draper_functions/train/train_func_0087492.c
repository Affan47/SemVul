symbol_in_math(const char *sPtr, int *inc)
{
	sPtr++;
	*inc = 0;
	for (int i = 0; i < NCODES; i++) {
		int len = strlen(symbol_code[i][0]);
		if (!strncmp(sPtr, symbol_code[i][0], len)) {
			*inc = len;
			return i;
		}
	}
	return -1;
}
