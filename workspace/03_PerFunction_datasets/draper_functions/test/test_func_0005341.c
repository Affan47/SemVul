ti_send(struct ti_port *tport)
{
	int count, result;
	struct usb_serial_port *port = tport->tp_port;
	unsigned long flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	if (tport->tp_write_urb_in_use)
		goto unlock;

	count = kfifo_out(&port->write_fifo,
				port->write_urb->transfer_buffer,
				port->bulk_out_size);

	if (count == 0)
		goto unlock;

	tport->tp_write_urb_in_use = 1;

	spin_unlock_irqrestore(&tport->tp_lock, flags);

	usb_serial_debug_data(&port->dev, __func__, count,
			      port->write_urb->transfer_buffer);

	usb_fill_bulk_urb(port->write_urb, port->serial->dev,
			   usb_sndbulkpipe(port->serial->dev,
					    port->bulk_out_endpointAddress),
			   port->write_urb->transfer_buffer, count,
			   ti_bulk_out_callback, tport);

	result = usb_submit_urb(port->write_urb, GFP_ATOMIC);
	if (result) {
		dev_err_console(port, "%s - submit write urb failed, %d\n",
							__func__, result);
		tport->tp_write_urb_in_use = 0;

	} else {
		spin_lock_irqsave(&tport->tp_lock, flags);
		port->icount.tx += count;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	}


	tty_port_tty_wakeup(&port->port);

	return;
unlock:
	spin_unlock_irqrestore(&tport->tp_lock, flags);
	return;
}
