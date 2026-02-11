printargv(tcp, addr)
struct tcb *tcp;
long addr;
{
	union {
		unsigned int p32;
		unsigned long p64;
		char data[sizeof(long)];
	} cp;
	char *sep;
	int n = 0;

	cp.p64 = 1;
	for (sep = ""; !abbrev(tcp) || n < max_strlen / 2; sep = ", ", ++n) {
		if (umoven(tcp, addr, personality_wordsize[current_personality],
			   cp.data) < 0) {
			tprintf("%#lx", addr);
			return;
		}
		if (personality_wordsize[current_personality] == 4)
			cp.p64 = cp.p32;
		if (cp.p64 == 0)
			break;
		tprintf("%s", sep);
		printstr(tcp, cp.p64, -1);
		addr += personality_wordsize[current_personality];
	}
	if (cp.p64)
		tprintf("%s...", sep);
}
