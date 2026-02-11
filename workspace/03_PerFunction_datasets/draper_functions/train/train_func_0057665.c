irtty_stop_receiver(struct tty_struct *tty, int stop)
{
	struct ktermios old_termios;
	int cflag;

	down_write(&tty->termios_rwsem);
	old_termios = tty->termios;
	cflag = tty->termios.c_cflag;

	if (stop)
		cflag &= ~CREAD;
	else
		cflag |= CREAD;

	tty->termios.c_cflag = cflag;
	if (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old_termios);
	up_write(&tty->termios_rwsem);
}
