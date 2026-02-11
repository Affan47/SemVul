cy_unthrottle(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_card *card;
	unsigned long flags;

#ifdef CY_DEBUG_THROTTLE
	printk(KERN_DEBUG "cyc:unthrottle %s: %ld...ttyC%d\n",
		tty_name(tty), tty_chars_in_buffer(tty), info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_unthrottle"))
		return;

	if (I_IXOFF(tty)) {
		if (info->x_char)
			info->x_char = 0;
		else
			cy_send_xchar(tty, START_CHAR(tty));
	}

	if (tty->termios.c_cflag & CRTSCTS) {
		card = info->card;
		if (!cy_is_Z(card)) {
			spin_lock_irqsave(&card->card_lock, flags);
			cyy_change_rts_dtr(info, TIOCM_RTS, 0);
			spin_unlock_irqrestore(&card->card_lock, flags);
		} else {
			info->throttle = 0;
		}
	}
}
