tty_ldisc_reinit(struct tty_struct *tty, int disc)
{
	struct tty_ldisc *ld;
	int retval;

	ld = tty_ldisc_get(tty, disc);
	if (IS_ERR(ld)) {
		BUG_ON(disc == N_TTY);
		return PTR_ERR(ld);
	}

	if (tty->ldisc) {
		tty_ldisc_close(tty, tty->ldisc);
		tty_ldisc_put(tty->ldisc);
	}


	tty->ldisc = ld;
	tty_set_termios_ldisc(tty, disc);
	retval = tty_ldisc_open(tty, tty->ldisc);
	if (retval) {
		if (!WARN_ON(disc == N_TTY)) {
			tty_ldisc_put(tty->ldisc);
			tty->ldisc = NULL;
		}
	}
	return retval;
}
