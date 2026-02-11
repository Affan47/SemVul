ti_port_probe(struct usb_serial_port *port)
{
	struct ti_port *tport;

	tport = kzalloc(sizeof(*tport), GFP_KERNEL);
	if (!tport)
		return -ENOMEM;

	spin_lock_init(&tport->tp_lock);
	if (port == port->serial->port[0])
		tport->tp_uart_base_addr = TI_UART1_BASE_ADDR;
	else
		tport->tp_uart_base_addr = TI_UART2_BASE_ADDR;
	port->port.closing_wait = msecs_to_jiffies(10 * closing_wait);
	tport->tp_port = port;
	tport->tp_tdev = usb_get_serial_data(port->serial);
	tport->tp_uart_mode = 0;

	usb_set_serial_port_data(port, tport);

	port->port.drain_delay = 3;

	return 0;
}
