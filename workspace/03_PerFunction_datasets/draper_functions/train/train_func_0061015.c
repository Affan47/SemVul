edge_tty_recv(struct usb_serial_port *port, unsigned char *data,
		int length)
{
	int cnt;

	cnt = tty_insert_flip_string(&port->port, data, length);
	if (cnt < length) {
		dev_err(&port->dev, "%s - dropping data, %d bytes lost\n",
				__func__, length - cnt);
	}
	data += cnt;
	length -= cnt;

	tty_flip_buffer_push(&port->port);
}
