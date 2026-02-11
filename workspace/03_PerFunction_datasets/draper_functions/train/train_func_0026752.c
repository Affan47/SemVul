usa2x_outdat_callback(struct urb *urb)
{
	struct usb_serial_port *port;
	struct keyspan_port_private *p_priv;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);
	dev_dbg(&port->dev, "%s - urb %d\n", __func__, urb == p_priv->out_urbs[1]);

	usb_serial_port_softint(port);
}
