bcm_uart_probe(struct platform_device *pdev)
{
	struct resource *res_mem, *res_irq;
	struct uart_port *port;
	struct clk *clk;
	int ret;

	if (pdev->dev.of_node)
		pdev->id = of_alias_get_id(pdev->dev.of_node, "uart");

	if (pdev->id < 0 || pdev->id >= BCM63XX_NR_UARTS)
		return -EINVAL;

	port = &ports[pdev->id];
	if (port->membase)
		return -EBUSY;
	memset(port, 0, sizeof(*port));

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res_mem)
		return -ENODEV;

	port->mapbase = res_mem->start;
	port->membase = devm_ioremap_resource(&pdev->dev, res_mem);
	if (IS_ERR(port->membase))
		return PTR_ERR(port->membase);

	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res_irq)
		return -ENODEV;

	clk = pdev->dev.of_node ? of_clk_get(pdev->dev.of_node, 0) :
				  clk_get(&pdev->dev, "periph");
	if (IS_ERR(clk))
		return -ENODEV;

	port->iotype = UPIO_MEM;
	port->irq = res_irq->start;
	port->ops = &bcm_uart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;
	port->fifosize = 16;
	port->uartclk = clk_get_rate(clk) / 2;
	port->line = pdev->id;
	clk_put(clk);

	ret = uart_add_one_port(&bcm_uart_driver, port);
	if (ret) {
		ports[pdev->id].membase = NULL;
		return ret;
	}
	platform_set_drvdata(pdev, port);
	return 0;
}
