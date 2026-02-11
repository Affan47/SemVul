n_tty_ioctl_helper(struct tty_struct *tty, struct file *file,
		       unsigned int cmd, unsigned long arg)
{
	int retval;

	switch (cmd) {
	case TCXONC:
		retval = tty_check_change(tty);
		if (retval)
			return retval;
		switch (arg) {
		case TCOOFF:
			spin_lock_irq(&tty->flow_lock);
			if (!tty->flow_stopped) {
				tty->flow_stopped = 1;
				__stop_tty(tty);
			}
			spin_unlock_irq(&tty->flow_lock);
			break;
		case TCOON:
			spin_lock_irq(&tty->flow_lock);
			if (tty->flow_stopped) {
				tty->flow_stopped = 0;
				__start_tty(tty);
			}
			spin_unlock_irq(&tty->flow_lock);
			break;
		case TCIOFF:
			if (STOP_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xchar(tty, STOP_CHAR(tty));
			break;
		case TCION:
			if (START_CHAR(tty) != __DISABLED_CHAR)
				retval = tty_send_xchar(tty, START_CHAR(tty));
			break;
		default:
			return -EINVAL;
		}
		return retval;
	case TCFLSH:
		retval = tty_check_change(tty);
		if (retval)
			return retval;
		return __tty_perform_flush(tty, arg);
	default:

		return tty_mode_ioctl(tty, file, cmd, arg);
	}
}
