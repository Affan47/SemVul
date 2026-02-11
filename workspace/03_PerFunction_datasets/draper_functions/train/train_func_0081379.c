set_termiox(struct tty_struct *tty, void __user *arg, int opt)
{
	struct termiox tnew;
	struct tty_ldisc *ld;

	if (tty->termiox == NULL)
		return -EINVAL;
	if (copy_from_user(&tnew, arg, sizeof(struct termiox)))
		return -EFAULT;

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

	down_write(&tty->termios_rwsem);
	if (tty->ops->set_termiox)
		tty->ops->set_termiox(tty, &tnew);
	up_write(&tty->termios_rwsem);
	return 0;
}
