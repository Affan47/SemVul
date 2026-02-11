cyberjack_port_probe(struct usb_serial_port *port)
{
	struct cyberjack_private *priv;
	int result;

	priv = kmalloc(sizeof(struct cyberjack_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->rdtodo = 0;
	priv->wrfilled = 0;
	priv->wrsent = 0;

	usb_set_serial_port_data(port, priv);

	result = usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL);
	if (result)
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");

	return 0;
}
