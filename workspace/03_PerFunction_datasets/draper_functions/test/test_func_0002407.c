do_kill(char c)
{
	int i, len;

	if (backslashed) {
		lbptr--;
		ansi_process_s("\b");
		do_data(c);
		return;
	}
	if (lnext) {
		do_data(c);
		return;
	}
	while (lbptr > lbuf) {
		len = strlen(ctl_see((int) *--lbptr));

		for (i = 0; i < len; i++)
			ansi_process_s("\b \b");
	}
}
