get_uptime(char *buf, ulonglong *j64p)
{
	ulong jiffies, tmp1, tmp2;
	ulonglong jiffies_64, wrapped;

	if (symbol_exists("jiffies_64")) {
		get_symbol_data("jiffies_64", sizeof(ulonglong), &jiffies_64);
		if (THIS_KERNEL_VERSION >= LINUX(2,6,0)) {
			wrapped = (jiffies_64 & 0xffffffff00000000ULL);
			if (wrapped) {
				wrapped -= 0x100000000ULL;
				jiffies_64 &= 0x00000000ffffffffULL;
				jiffies_64 |= wrapped;
                		jiffies_64 += (ulonglong)(300*machdep->hz);
			} else {
				tmp1 = (ulong)(uint)(-300*machdep->hz);
				tmp2 = (ulong)jiffies_64;
				jiffies_64 = (ulonglong)(tmp2 - tmp1);
			}
		}
		if (buf)
			convert_time(jiffies_64, buf);
		if (j64p)
			*j64p = jiffies_64;
	} else {
		get_symbol_data("jiffies", sizeof(long), &jiffies);
		if (buf)
			convert_time((ulonglong)jiffies, buf);
		if (j64p)
			*j64p = (ulonglong)jiffies;
	}

	return buf;
}
