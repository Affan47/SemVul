set_termios(struct tty_struct *tty, void __user *arg, int opt)
{
	struct ktermios tmp_termios;
	struct tty_ldisc *ld;
	int retval = tty_check_change(tty);

	if (retval)
		return retval;

	down_read(&tty->termios_rwsem);
	tmp_termios = tty->termios;
	up_read(&tty->termios_rwsem);

	if (opt & TERMIOS_TERMIO) {
		if (user_termio_to_kernel_termios(&tmp_termios,
						(struct termio __user *)arg))
			return -EFAULT;
#ifdef TCGETS2
	} else if (opt & TERMIOS_OLD) {
		if (user_termios_to_kernel_termios_1(&tmp_termios,
						(struct termios __user *)arg))
			return -EFAULT;
	} else {
		if (user_termios_to_kernel_termios(&tmp_termios,
						(struct termios2 __user *)arg))
			return -EFAULT;
	}
#else
	} else if (user_termios_to_kernel_termios(&tmp_termios,
					(struct termios __user *)arg))
		return -EFAULT;
#endif


	tmp_termios.c_ispeed = tty_termios_input_baud_rate(&tmp_termios);
	tmp_termios.c_ospeed = tty_termios_baud_rate(&tmp_termios);

	ld = tty_ldisc_ref(tty);

	if (ld != NULL) {
		if ((opt & TERMIOS_FLUSH) && ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		tty_ldisc_deref(ld);
	}

	if (opt & TERMIOS_WAIT) {
		tty_wait_until_sent(tty, 0);
		if (signal_pending(current))
			return -ERESTARTSYS;
	}

	tty_set_termios(tty, &tmp_termios);


	return 0;
}
