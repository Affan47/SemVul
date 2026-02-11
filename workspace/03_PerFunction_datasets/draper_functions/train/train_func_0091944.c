keyspan_tiocmset(struct tty_struct *tty,
			    unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private *p_priv = usb_get_serial_port_data(port);

	if (set & TIOCM_RTS)
		p_priv->rts_state = 1;
	if (set & TIOCM_DTR)
		p_priv->dtr_state = 1;
	if (clear & TIOCM_RTS)
		p_priv->rts_state = 0;
	if (clear & TIOCM_DTR)
		p_priv->dtr_state = 0;
	keyspan_send_setup(port, 0);
	return 0;
}
