atmel_console_init(void)
{
	int ret;
	if (atmel_default_console_device) {
		struct atmel_uart_data *pdata =
			dev_get_platdata(&atmel_default_console_device->dev);
		int id = pdata->num;
		struct atmel_uart_port *port = &atmel_ports[id];

		port->backup_imr = 0;
		port->uart.line = id;

		add_preferred_console(ATMEL_DEVICENAME, id, NULL);
		ret = atmel_init_port(port, atmel_default_console_device);
		if (ret)
			return ret;
		register_console(&atmel_console);
	}

	return 0;
}
