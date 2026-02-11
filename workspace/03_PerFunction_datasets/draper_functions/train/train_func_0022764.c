php_sprintf_append2n(char **buffer, int *pos, int *size, long number,
					 int width, char padding, int alignment, int n,
					 char *chartable, int expprec)
{
	char numbuf[NUM_BUF_SIZE];
	register unsigned long num;
	register unsigned int  i = NUM_BUF_SIZE - 1;
	register int andbits = (1 << n) - 1;

	PRINTF_DEBUG(("sprintf: append2n(%x, %x, %x, %d, %d, '%c', %d, %d, %x)\n",
				  *buffer, pos, size, number, width, padding, alignment, n,
				  chartable));
	PRINTF_DEBUG(("sprintf: append2n 2^%d andbits=%x\n", n, andbits));

	num = (unsigned long) number;
	numbuf[i] = '\0';

	do {
		numbuf[--i] = chartable[(num & andbits)];
		num >>= n;
	}
	while (num > 0);

	php_sprintf_appendstring(buffer, pos, size, &numbuf[i], width, 0,
							 padding, alignment, (NUM_BUF_SIZE - 1) - i,
							 0, expprec, 0);
}
