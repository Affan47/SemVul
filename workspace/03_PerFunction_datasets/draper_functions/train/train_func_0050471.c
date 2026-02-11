bnstr2bin(uint64 &u64, const char *&str, int base)
{
	u64 = 0;
	uint64 ubase = base;
	int i = 0;
	do {
		int c = hexdigit(*str);
		if (c == -1 || c >= base) return (i == 0) ? false : true;
		u64 *= ubase;
		u64 += c;
		str++;
		i++;
	} while (*str);
	return true;
}
