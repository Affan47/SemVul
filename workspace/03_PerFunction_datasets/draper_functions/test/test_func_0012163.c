mos7720_bulk_out_data_callback(struct urb *urb)
{
	struct moschip_port *mos7720_port;
	int status = urb->status;

	if (status) {
		dev_dbg(&urb->dev->dev, "nonzero write bulk status received:%d\n", status);
		return;
	}

	mos7720_port = urb->context;
	if (!mos7720_port) {
		dev_dbg(&urb->dev->dev, "NULL mos7720_port pointer\n");
		return ;
	}

	if (mos7720_port->open)
		tty_port_tty_wakeup(&mos7720_port->port->port);
}
