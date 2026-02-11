hso_std_serial_write_bulk_callback(struct urb *urb)
{
	struct hso_serial *serial = urb->context;
	int status = urb->status;


	if (!serial) {
		D1("serial == NULL");
		return;
	}

	spin_lock(&serial->serial_lock);
	serial->tx_urb_used = 0;
	spin_unlock(&serial->serial_lock);
	if (status) {
		handle_usb_error(status, __func__, serial->parent);
		return;
	}
	hso_put_activity(serial->parent);
	tty_port_tty_wakeup(&serial->port);
	hso_kick_transmit(serial);

	D1(" ");
}
