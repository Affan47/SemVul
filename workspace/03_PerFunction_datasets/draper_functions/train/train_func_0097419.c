qt2_process_read_urb(struct urb *urb)
{
	struct usb_serial *serial;
	struct qt2_serial_private *serial_priv;
	struct usb_serial_port *port;
	struct qt2_port_private *port_priv;
	bool escapeflag;
	unsigned char *ch;
	int i;
	unsigned char newport;
	int len = urb->actual_length;

	if (!len)
		return;

	ch = urb->transfer_buffer;
	serial = urb->context;
	serial_priv = usb_get_serial_data(serial);
	port = serial->port[serial_priv->current_port];
	port_priv = usb_get_serial_port_data(port);

	for (i = 0; i < urb->actual_length; i++) {
		ch = (unsigned char *)urb->transfer_buffer + i;
		if ((i <= (len - 3)) &&
		    (*ch == QT2_CONTROL_BYTE) &&
		    (*(ch + 1) == QT2_CONTROL_BYTE)) {
			escapeflag = false;
			switch (*(ch + 2)) {
			case QT2_LINE_STATUS:
			case QT2_MODEM_STATUS:
				if (i > (len - 4)) {
					dev_warn(&port->dev,
						 "%s - status message too short\n",
						__func__);
					break;
				}
				qt2_process_status(port, ch + 2);
				i += 3;
				escapeflag = true;
				break;
			case QT2_XMIT_HOLD:
				if (i > (len - 5)) {
					dev_warn(&port->dev,
						 "%s - xmit_empty message too short\n",
						 __func__);
					break;
				}
				qt2_process_xmit_empty(port, ch + 3);
				i += 4;
				escapeflag = true;
				break;
			case QT2_CHANGE_PORT:
				if (i > (len - 4)) {
					dev_warn(&port->dev,
						 "%s - change_port message too short\n",
						 __func__);
					break;
				}
				tty_flip_buffer_push(&port->port);

				newport = *(ch + 3);

				if (newport > serial->num_ports) {
					dev_err(&port->dev,
						"%s - port change to invalid port: %i\n",
						__func__, newport);
					break;
				}

				serial_priv->current_port = newport;
				port = serial->port[serial_priv->current_port];
				port_priv = usb_get_serial_port_data(port);
				i += 3;
				escapeflag = true;
				break;
			case QT2_REC_FLUSH:
			case QT2_XMIT_FLUSH:
				qt2_process_flush(port, ch + 2);
				i += 2;
				escapeflag = true;
				break;
			case QT2_CONTROL_ESCAPE:
				tty_buffer_request_room(&port->port, 2);
				tty_insert_flip_string(&port->port, ch, 2);
				i += 2;
				escapeflag = true;
				break;
			default:
				dev_warn(&port->dev,
					 "%s - unsupported command %i\n",
					 __func__, *(ch + 2));
				break;
			}
			if (escapeflag)
				continue;
		}

		tty_buffer_request_room(&port->port, 1);
		tty_insert_flip_string(&port->port, ch, 1);
	}

	tty_flip_buffer_push(&port->port);
}
