ch_ungetchar(c)
	int c;
{
	if (c != -1 && ch_ungotchar != -1)
		error("ch_ungetchar overrun", NULL_PARG);
	ch_ungotchar = c;
}
