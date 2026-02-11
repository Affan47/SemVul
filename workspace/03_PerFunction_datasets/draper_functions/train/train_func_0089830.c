moxa_tiocmget(struct tty_struct *tty)
{
	struct moxa_port *ch = tty->driver_data;
	int flag = 0, dtr, rts;

	MoxaPortGetLineOut(ch, &dtr, &rts);
	if (dtr)
		flag |= TIOCM_DTR;
	if (rts)
		flag |= TIOCM_RTS;
	dtr = MoxaPortLineStatus(ch);
	if (dtr & 1)
		flag |= TIOCM_CTS;
	if (dtr & 2)
		flag |= TIOCM_DSR;
	if (dtr & 4)
		flag |= TIOCM_CD;
	return flag;
}
