mxuport_set_termios(struct tty_struct *tty,
				struct usb_serial_port *port,
				struct ktermios *old_termios)
{
	struct usb_serial *serial = port->serial;
	u8 *buf;
	u8 data_bits;
	u8 stop_bits;
	u8 parity;
	int baud;
	int err;

	if (old_termios &&
	    !tty_termios_hw_change(&tty->termios, old_termios) &&
	    tty->termios.c_iflag == old_termios->c_iflag) {
		dev_dbg(&port->dev, "%s - nothing to change\n", __func__);
		return;
	}

	buf = kmalloc(4, GFP_KERNEL);
	if (!buf)
		return;


	switch (C_CSIZE(tty)) {
	case CS5:
		data_bits = MX_WORDLENGTH_5;
		break;
	case CS6:
		data_bits = MX_WORDLENGTH_6;
		break;
	case CS7:
		data_bits = MX_WORDLENGTH_7;
		break;
	case CS8:
	default:
		data_bits = MX_WORDLENGTH_8;
		break;
	}


	if (C_PARENB(tty)) {
		if (C_CMSPAR(tty)) {
			if (C_PARODD(tty))
				parity = MX_PARITY_MARK;
			else
				parity = MX_PARITY_SPACE;
		} else {
			if (C_PARODD(tty))
				parity = MX_PARITY_ODD;
			else
				parity = MX_PARITY_EVEN;
		}
	} else {
		parity = MX_PARITY_NONE;
	}


	if (C_CSTOPB(tty))
		stop_bits = MX_STOP_BITS_2;
	else
		stop_bits = MX_STOP_BITS_1;

	buf[0] = data_bits;
	buf[1] = parity;
	buf[2] = stop_bits;
	buf[3] = 0;

	err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_SET_LINE,
					 0, port->port_number, buf, 4);
	if (err)
		goto out;

	err = mxuport_set_termios_flow(tty, old_termios, port, serial);
	if (err)
		goto out;

	baud = tty_get_baud_rate(tty);
	if (!baud)
		baud = 9600;


	put_unaligned_le32(baud, buf);

	err = mxuport_send_ctrl_data_urb(serial, RQ_VENDOR_SET_BAUD,
					 0, port->port_number,
					 buf, 4);
	if (err)
		goto out;

	dev_dbg(&port->dev, "baud_rate	: %d\n", baud);
	dev_dbg(&port->dev, "data_bits	: %d\n", data_bits);
	dev_dbg(&port->dev, "parity	: %d\n", parity);
	dev_dbg(&port->dev, "stop_bits	: %d\n", stop_bits);

out:
	kfree(buf);
}
