serial8250_init(void)
{
	int ret;

	if (nr_uarts == 0)
		return -ENODEV;

	serial8250_isa_init_ports();

	printk(KERN_INFO "Serial: 8250/16550 driver, "
		"%d ports, IRQ sharing %sabled\n", nr_uarts,
		share_irqs ? "en" : "dis");

#ifdef CONFIG_SPARC
	ret = sunserial_register_minors(&serial8250_reg, UART_NR);
#else
	serial8250_reg.nr = UART_NR;
	ret = uart_register_driver(&serial8250_reg);
#endif
	if (ret)
		goto out;

	ret = serial8250_pnp_init();
	if (ret)
		goto unreg_uart_drv;

	serial8250_isa_devs = platform_device_alloc("serial8250",
						    PLAT8250_DEV_LEGACY);
	if (!serial8250_isa_devs) {
		ret = -ENOMEM;
		goto unreg_pnp;
	}

	ret = platform_device_add(serial8250_isa_devs);
	if (ret)
		goto put_dev;

	serial8250_register_ports(&serial8250_reg, &serial8250_isa_devs->dev);

	ret = platform_driver_register(&serial8250_isa_driver);
	if (ret == 0)
		goto out;

	platform_device_del(serial8250_isa_devs);
put_dev:
	platform_device_put(serial8250_isa_devs);
unreg_pnp:
	serial8250_pnp_exit();
unreg_uart_drv:
#ifdef CONFIG_SPARC
	sunserial_unregister_minors(&serial8250_reg, UART_NR);
#else
	uart_unregister_driver(&serial8250_reg);
#endif
out:
	return ret;
}
