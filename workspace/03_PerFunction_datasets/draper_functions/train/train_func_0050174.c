flush_blanks()
{
	int half, i, nb;

	half = 0;
	nb = nblank_lines;
	if (nb & 1) {
		if (fine)
			half = 1;
		else
			nb++;
	}
	nb /= 2;
	for (i = nb; --i >= 0;)
		PUTC('\n');
	if (half) {
		PUTC('\033');
		PUTC('9');
		if (!nb)
			PUTC('\r');
	}
	nblank_lines = 0;
}
