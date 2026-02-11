cpuspeed(void)
{
	int loops;
	ulong end_low, end_high;

	if (cpu_id.fid.bits.rdtsc == 0 ) {
		return(-1);
	}


	outb((inb(0x61) & ~0x02) | 0x01, 0x61);
	outb(0xb0, 0x43);
	outb(TICKS & 0xff, 0x42);
	outb(TICKS >> 8, 0x42);

	asm __volatile__ ("rdtsc":"=a" (stlow),"=d" (sthigh));

	loops = 0;
	do {
		loops++;
	} while ((inb(0x61) & 0x20) == 0);

	asm __volatile__ (
		"rdtsc\n\t" \
		"subl stlow,%%eax\n\t" \
		"sbbl sthigh,%%edx\n\t" \
		:"=a" (end_low), "=d" (end_high)
	);


	if (loops < 4 || end_low < 50000) {
		return(-1);
	}
	v->clks_msec = end_low/50;

	if (tsc_invariable) end_low = correct_tsc(end_low);

	return(v->clks_msec);
}
