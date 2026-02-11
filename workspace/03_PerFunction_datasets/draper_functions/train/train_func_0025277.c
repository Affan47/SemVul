keyspan_pda_write(struct tty_struct *tty,
	struct usb_serial_port *port, const unsigned char *buf, int count)
{
	struct usb_serial *serial = port->serial;
	int request_unthrottle = 0;
	int rc = 0;
	struct keyspan_pda_private *priv;

	priv = usb_get_serial_port_data(port);


	if (count == 0) {
		dev_dbg(&port->dev, "write request of 0 bytes\n");
		return 0;
	}


	spin_lock_bh(&port->lock);
	if (!test_bit(0, &port->write_urbs_free) || priv->tx_throttled) {
		spin_unlock_bh(&port->lock);
		return 0;
	}
	clear_bit(0, &port->write_urbs_free);
	spin_unlock_bh(&port->lock);


	count = (count > port->bulk_out_size) ? port->bulk_out_size : count;


	if (count > priv->tx_room && !in_interrupt()) {
		u8 *room;

		room = kmalloc(1, GFP_KERNEL);
		if (!room) {
			rc = -ENOMEM;
			goto exit;
		}

		rc = usb_control_msg(serial->dev,
				     usb_rcvctrlpipe(serial->dev, 0),
				     6,
				     USB_TYPE_VENDOR | USB_RECIP_INTERFACE
				     | USB_DIR_IN,
				     0,
				     0,
				     room,
				     1,
				     2000);
		if (rc > 0) {
			dev_dbg(&port->dev, "roomquery says %d\n", *room);
			priv->tx_room = *room;
		}
		kfree(room);
		if (rc < 0) {
			dev_dbg(&port->dev, "roomquery failed\n");
			goto exit;
		}
		if (rc == 0) {
			dev_dbg(&port->dev, "roomquery returned 0 bytes\n");
			rc = -EIO;
			goto exit;
		}
	}
	if (count > priv->tx_room) {


		count = priv->tx_room;
		request_unthrottle = 1;
	}

	if (count) {

		memcpy(port->write_urb->transfer_buffer, buf, count);

		port->write_urb->transfer_buffer_length = count;

		priv->tx_room -= count;

		rc = usb_submit_urb(port->write_urb, GFP_ATOMIC);
		if (rc) {
			dev_dbg(&port->dev, "usb_submit_urb(write bulk) failed\n");
			goto exit;
		}
	} else {


		request_unthrottle = 1;
	}

	if (request_unthrottle) {
		priv->tx_throttled = 1;
		schedule_work(&priv->unthrottle_work);
	}

	rc = count;
exit:
	if (rc < 0)
		set_bit(0, &port->write_urbs_free);
	return rc;
}
