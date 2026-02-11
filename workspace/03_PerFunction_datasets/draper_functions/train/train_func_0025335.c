send_prepostfix(int flag, char data)
{
	char feed;

	DEBUG_CTERM("send_prepostfix: flag =%d, data=%d\n", flag, data);
	if (flag == 0)
		return;

	if (flag == 1 && data)
	{
		int i;

		feed = '\r';
		tty_write(&feed, 1);
		feed = '\n';
		for (i=0; i<data - skip_next_lf; i++)
			tty_write(&feed, 1);
		skip_next_lf = 0;
	}
	if (flag == 2)
		tty_write(&data, 1);
}
