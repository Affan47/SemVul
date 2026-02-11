sierra_submit_delayed_urbs(struct usb_serial_port *port)
{
	struct sierra_port_private *portdata = usb_get_serial_port_data(port);
	struct sierra_intf_private *intfdata;
	struct urb *urb;
	int ec = 0;
	int err;

	intfdata = usb_get_serial_data(port->serial);

	for (;;) {
		urb = usb_get_from_anchor(&portdata->delayed);
		if (!urb)
			break;

		usb_anchor_urb(urb, &portdata->active);
		intfdata->in_flight++;
		err = usb_submit_urb(urb, GFP_ATOMIC);
		if (err) {
			dev_err(&port->dev, "%s - submit urb failed: %d",
					__func__, err);
			ec++;
			intfdata->in_flight--;
			usb_unanchor_urb(urb);
			kfree(urb->transfer_buffer);
			usb_free_urb(urb);

			spin_lock(&portdata->lock);
			portdata->outstanding_urbs--;
			spin_unlock(&portdata->lock);
		}
	}

	if (ec)
		return -EIO;

	return 0;
}
