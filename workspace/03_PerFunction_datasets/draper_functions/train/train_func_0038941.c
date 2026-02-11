ipwireless_tty_init(void)
{
	int result;

	ipw_tty_driver = alloc_tty_driver(IPWIRELESS_PCMCIA_MINORS);
	if (!ipw_tty_driver)
		return -ENOMEM;

	ipw_tty_driver->driver_name = IPWIRELESS_PCCARD_NAME;
	ipw_tty_driver->name = "ttyIPWp";
	ipw_tty_driver->major = 0;
	ipw_tty_driver->minor_start = IPWIRELESS_PCMCIA_START;
	ipw_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	ipw_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	ipw_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	ipw_tty_driver->init_termios = tty_std_termios;
	ipw_tty_driver->init_termios.c_cflag =
	    B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	ipw_tty_driver->init_termios.c_ispeed = 9600;
	ipw_tty_driver->init_termios.c_ospeed = 9600;
	tty_set_operations(ipw_tty_driver, &tty_ops);
	result = tty_register_driver(ipw_tty_driver);
	if (result) {
		printk(KERN_ERR IPWIRELESS_PCCARD_NAME
		       ": failed to register tty driver\n");
		put_tty_driver(ipw_tty_driver);
		return result;
	}

	return 0;
}
