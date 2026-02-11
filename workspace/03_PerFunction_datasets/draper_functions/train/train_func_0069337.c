garmin_read_bulk_callback(struct urb *urb)
{
	unsigned long flags;
	struct usb_serial_port *port = urb->context;
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	unsigned char *data = urb->transfer_buffer;
	int status = urb->status;
	int retval;

	if (status) {
		dev_dbg(&urb->dev->dev, "%s - nonzero read bulk status received: %d\n",
			__func__, status);
		return;
	}

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	garmin_read_process(garmin_data_p, data, urb->actual_length, 1);

	if (urb->actual_length == 0 &&
			0 != (garmin_data_p->flags & FLAGS_BULK_IN_RESTART)) {
		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags &= ~FLAGS_BULK_IN_RESTART;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		retval = usb_submit_urb(port->read_urb, GFP_ATOMIC);
		if (retval)
			dev_err(&port->dev,
				"%s - failed resubmitting read urb, error %d\n",
				__func__, retval);
	} else if (urb->actual_length > 0) {

		if (0 == (garmin_data_p->flags & FLAGS_THROTTLED)) {
			retval = usb_submit_urb(port->read_urb, GFP_ATOMIC);
			if (retval)
				dev_err(&port->dev,
					"%s - failed resubmitting read urb, error %d\n",
					__func__, retval);
		}
	} else {
		dev_dbg(&port->dev, "%s - end of bulk data\n", __func__);
		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags &= ~FLAGS_BULK_IN_ACTIVE;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);
	}
}
