timbuart_probe(struct platform_device *dev)
{
	int err, irq;
	struct timbuart_port *uart;
	struct resource *iomem;

	dev_dbg(&dev->dev, "%s\n", __func__);

	uart = kzalloc(sizeof(*uart), GFP_KERNEL);
	if (!uart) {
		err = -EINVAL;
		goto err_mem;
	}

	uart->usedma = 0;

	uart->port.uartclk = 3250000 * 16;
	uart->port.fifosize  = TIMBUART_FIFO_SIZE;
	uart->port.regshift  = 2;
	uart->port.iotype  = UPIO_MEM;
	uart->port.ops = &timbuart_ops;
	uart->port.irq = 0;
	uart->port.flags = UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	uart->port.line  = 0;
	uart->port.dev	= &dev->dev;

	iomem = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!iomem) {
		err = -ENOMEM;
		goto err_register;
	}
	uart->port.mapbase = iomem->start;
	uart->port.membase = NULL;

	irq = platform_get_irq(dev, 0);
	if (irq < 0) {
		err = -EINVAL;
		goto err_register;
	}
	uart->port.irq = irq;

	tasklet_init(&uart->tasklet, timbuart_tasklet, (unsigned long)uart);

	err = uart_register_driver(&timbuart_driver);
	if (err)
		goto err_register;

	err = uart_add_one_port(&timbuart_driver, &uart->port);
	if (err)
		goto err_add_port;

	platform_set_drvdata(dev, uart);

	return 0;

err_add_port:
	uart_unregister_driver(&timbuart_driver);
err_register:
	kfree(uart);
err_mem:
	printk(KERN_ERR "timberdale: Failed to register Timberdale UART: %d\n",
		err);

	return err;
}
