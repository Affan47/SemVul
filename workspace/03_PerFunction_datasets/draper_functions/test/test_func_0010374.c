failsafe(int msec, int scs)
{
	int ip;
	ulong sh, sl, l, h, t;
	unsigned char c;

	cprint(18, 22, "Press *F1* to enter Fail-Safe Mode");

	ip = 0;

	asm __volatile__(
		"rdtsc":"=a" (sl),"=d" (sh));


	while (1) {
		asm __volatile__(
			"rdtsc":"=a" (l),"=d" (h));
		asm __volatile__ (
			"subl %2,%0\n\t"
			"sbbl %3,%1"
			:"=a" (l), "=d" (h)
			:"g" (sl), "g" (sh),
			"0" (l), "1" (h));

		t = h * ((unsigned)0xffffffff / v->clks_msec);
		t += (l / v->clks_msec);


		if (t >= msec) {
			cprint(18, 22, "                                  ");
			break;
		}


		c = get_key();
		c &= 0x7f;

		if(c == scs) {
			fail_safe = 1;
			cprint(18, 22, "                                  ");
			break;
		}
	}
}
