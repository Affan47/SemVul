do_cerase(char c)
{
	int len;

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
	if (lbptr > lbuf) {
		len = strlen(ctl_see((int) *--lbptr));

		while (len--)
			ansi_process_s("\b \b");
	}
}
