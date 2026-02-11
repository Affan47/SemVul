cy_throttle(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_card *card;
	unsigned long flags;

#ifdef CY_DEBUG_THROTTLE
	printk(KERN_DEBUG "cyc:throttle %s: %ld...ttyC%d\n", tty_name(tty),
			tty->ldisc.chars_in_buffer(tty), info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_throttle"))
		return;

	card = info->card;

	if (I_IXOFF(tty)) {
		if (!cy_is_Z(card))
			cy_send_xchar(tty, STOP_CHAR(tty));
		else
			info->throttle = 1;
	}

	if (tty->termios.c_cflag & CRTSCTS) {
		if (!cy_is_Z(card)) {
			spin_lock_irqsave(&card->card_lock, flags);
			cyy_change_rts_dtr(info, 0, TIOCM_RTS);
			spin_unlock_irqrestore(&card->card_lock, flags);
		} else {
			info->throttle = 1;
		}
	}
}
