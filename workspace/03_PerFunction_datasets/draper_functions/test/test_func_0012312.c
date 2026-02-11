fwtty_port_carrier_raised(struct tty_port *tty_port)
{
	struct fwtty_port *port = to_port(tty_port, port);
	int rc;

	rc = (port->mstatus & TIOCM_CAR);

	fwtty_dbg(port, "%d\n", rc);

	return rc;
}
