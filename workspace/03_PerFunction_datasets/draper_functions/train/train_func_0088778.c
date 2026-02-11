vty_init(const struct file_operations *console_fops)
{
	cdev_init(&vc0_cdev, console_fops);
	if (cdev_add(&vc0_cdev, MKDEV(TTY_MAJOR, 0), 1) ||
	    register_chrdev_region(MKDEV(TTY_MAJOR, 0), 1, "/dev/vc/0") < 0)
		panic("Couldn't register /dev/tty0 driver\n");
	tty0dev = device_create_with_groups(tty_class, NULL,
					    MKDEV(TTY_MAJOR, 0), NULL,
					    vt_dev_groups, "tty0");
	if (IS_ERR(tty0dev))
		tty0dev = NULL;

	vcs_init();

	console_driver = alloc_tty_driver(MAX_NR_CONSOLES);
	if (!console_driver)
		panic("Couldn't allocate console driver\n");

	console_driver->name = "tty";
	console_driver->name_base = 1;
	console_driver->major = TTY_MAJOR;
	console_driver->minor_start = 1;
	console_driver->type = TTY_DRIVER_TYPE_CONSOLE;
	console_driver->init_termios = tty_std_termios;
	if (default_utf8)
		console_driver->init_termios.c_iflag |= IUTF8;
	console_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_RESET_TERMIOS;
	tty_set_operations(console_driver, &con_ops);
	if (tty_register_driver(console_driver))
		panic("Couldn't register console driver\n");
	kbd_init();
	console_map_init();
#ifdef CONFIG_MDA_CONSOLE
	mda_console_init();
#endif
	return 0;
}
