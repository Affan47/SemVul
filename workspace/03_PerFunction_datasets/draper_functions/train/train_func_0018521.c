putchr_raw(c)
	int c;
{
	if (need_clr)
	{
		need_clr = 0;
		clear_bot();
	}
#if MSDOS_COMPILER
	if (c == '\n' && is_tty)
	{

		putchr_raw('\r');
	}
#else
#ifdef _OSK
	if (c == '\n' && is_tty)
		putchr_raw(0x0A);
#endif
#endif


	if (ob >= &obuf[sizeof(obuf)-1])
		flush();
	*ob++ = c;
	return (c);
}
