PUTC(FILE *f, int c, int width)
{
	long put = 1;

	fputc(c, f);
	while (--width > 0)
	{
		fputc(' ', f);
		put++;
	}

	return put;
}
