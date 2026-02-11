gsmtty_throttle(struct tty_struct *tty)
{
	struct gsm_dlci *dlci = tty->driver_data;
	if (dlci->state == DLCI_CLOSED)
		return;
	if (tty->termios.c_cflag & CRTSCTS)
		dlci->modem_tx &= ~TIOCM_DTR;
	dlci->throttled = 1;

	gsmtty_modem_update(dlci, 0);
}
