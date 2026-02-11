keyspan_pda_port_probe(struct usb_serial_port *port)
{

	struct keyspan_pda_private *priv;

	priv = kmalloc(sizeof(struct keyspan_pda_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_WORK(&priv->wakeup_work, keyspan_pda_wakeup_write);
	INIT_WORK(&priv->unthrottle_work, keyspan_pda_request_unthrottle);
	priv->serial = port->serial;
	priv->port = port;

	usb_set_serial_port_data(port, priv);

	return 0;
}
