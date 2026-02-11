isicom_set_termios(struct tty_struct *tty,
	struct ktermios *old_termios)
{
	struct isi_port *port = tty->driver_data;
	unsigned long flags;

	if (isicom_paranoia_check(port, tty->name, "isicom_set_termios"))
		return;

	if (tty->termios.c_cflag == old_termios->c_cflag &&
			tty->termios.c_iflag == old_termios->c_iflag)
		return;

	spin_lock_irqsave(&port->card->card_lock, flags);
	isicom_config_port(tty);
	spin_unlock_irqrestore(&port->card->card_lock, flags);

	if ((old_termios->c_cflag & CRTSCTS) &&
			!(tty->termios.c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		isicom_start(tty);
	}
}
