ntty_cflags_changed(struct port *port, unsigned long flags,
		struct async_icount *cprev)
{
	const struct async_icount cnow = port->tty_icount;
	int ret;

	ret =	((flags & TIOCM_RNG) && (cnow.rng != cprev->rng)) ||
		((flags & TIOCM_DSR) && (cnow.dsr != cprev->dsr)) ||
		((flags & TIOCM_CD)  && (cnow.dcd != cprev->dcd)) ||
		((flags & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	return ret;
}
