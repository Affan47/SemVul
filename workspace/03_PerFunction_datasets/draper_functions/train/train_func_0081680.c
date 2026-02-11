ipaq_open(struct tty_struct *tty,
			struct usb_serial_port *port)
{
	struct usb_serial	*serial = port->serial;
	int			result = 0;
	int			retries = connect_retries;

	msleep(1000*initial_wait);


	while (retries) {
		retries--;
		result = usb_control_msg(serial->dev,
				usb_sndctrlpipe(serial->dev, 0), 0x22, 0x21,
				0x1, 0, NULL, 0, 100);
		if (!result)
			break;

		msleep(1000);
	}
	if (!retries && result) {
		dev_err(&port->dev, "%s - failed doing control urb, error %d\n",
							__func__, result);
		return result;
	}

	return usb_serial_generic_open(tty, port);
}
