memwatch_dump (int num)
{
	TCHAR *buf;
	int multiplier = num < 0 ? MEMWATCH_TOTAL : 1;

	buf = xmalloc (TCHAR, 50 * multiplier);
	if (!buf)
		return;
	memwatch_dump2 (buf, 50 * multiplier, num);
	f_out (stdout, _T("%s"), buf);
	xfree (buf);
}
