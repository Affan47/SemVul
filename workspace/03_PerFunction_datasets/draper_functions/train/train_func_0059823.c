usa28_instat_callback(struct urb *urb)
{
	int					err;
	unsigned char 				*data = urb->transfer_buffer;
	struct keyspan_usa28_portStatusMessage	*msg;
	struct usb_serial			*serial;
	struct usb_serial_port			*port;
	struct keyspan_port_private	 	*p_priv;
	int old_dcd_state;
	int status = urb->status;

	serial =  urb->context;

	if (status) {
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %x\n", __func__, status);
		return;
	}

	if (urb->actual_length != sizeof(struct keyspan_usa28_portStatusMessage)) {
		dev_dbg(&urb->dev->dev, "%s - bad length %d\n", __func__, urb->actual_length);
		goto exit;
	}

	msg = (struct keyspan_usa28_portStatusMessage *)data;


	if (msg->port >= serial->num_ports) {
		dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n", __func__, msg->port);
		goto exit;
	}
	port = serial->port[msg->port];
	p_priv = usb_get_serial_port_data(port);
	if (!p_priv)
		goto resubmit;


	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->cts) ? 1 : 0);
	p_priv->dsr_state = ((msg->dsr) ? 1 : 0);
	p_priv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_priv->ri_state = ((msg->ri) ? 1 : 0);

	if (old_dcd_state != p_priv->dcd_state && old_dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
exit: ;
}
