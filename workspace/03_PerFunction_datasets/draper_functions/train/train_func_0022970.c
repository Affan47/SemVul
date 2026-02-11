capinc_tty_unthrottle(struct tty_struct *tty)
{
	struct capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_unthrottle\n");
	mp->ttyinstop = 0;
	handle_minor_recv(mp);
}
