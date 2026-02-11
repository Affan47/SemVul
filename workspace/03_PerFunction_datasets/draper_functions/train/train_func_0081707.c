cterm_process_write(char *buf, int len)
{
	unsigned short flags = buf[1] | buf[2]<<8;
	char  prefixdata  = buf[3];
	char  postfixdata = buf[4];
	char  feed = '\n';


	DEBUG_CTERM("process_write flags = %x (prefix=%d, postfix=%d)\n",flags, prefixdata, postfixdata);

	tty_set_discard(!(flags >> 3));

	send_prepostfix(((flags >> 6) & 3), prefixdata);

	if (skip_next_lf)
	{
		skip_first_lf(buf+4, len-4);
	}

	tty_write(buf+4, len-4);

	if ((flags >> 2)&1)
	{
		if (!skip_next_lf)
		{
			DEBUG_CTERM("sending feed, skipping next LF\n");
			tty_write(&feed, 1);
			skip_next_lf = 1;
		}
		else
		{
			DEBUG_CTERM("NOT sending feed, skip_next_lf set\n");
			skip_next_lf = 0;
		}
	}

	send_prepostfix(((flags >> 8) & 3), postfixdata);


	if ((flags >> 10) & 1)
		send_write_complete();

	return len;
}
