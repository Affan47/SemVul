mid8250_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct uart_8250_port uart;
	struct mid8250 *mid;
	unsigned int bar;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	pci_set_master(pdev);

	mid = devm_kzalloc(&pdev->dev, sizeof(*mid), GFP_KERNEL);
	if (!mid)
		return -ENOMEM;

	mid->board = (struct mid8250_board *)id->driver_data;
	bar = FL_GET_BASE(mid->board->flags);

	memset(&uart, 0, sizeof(struct uart_8250_port));

	uart.port.dev = &pdev->dev;
	uart.port.irq = pdev->irq;
	uart.port.private_data = mid;
	uart.port.type = PORT_16750;
	uart.port.iotype = UPIO_MEM;
	uart.port.uartclk = mid->board->base_baud * 16;
	uart.port.flags = UPF_SHARE_IRQ | UPF_FIXED_PORT | UPF_FIXED_TYPE;
	uart.port.set_termios = mid8250_set_termios;

	uart.port.mapbase = pci_resource_start(pdev, bar);
	uart.port.membase = pcim_iomap(pdev, bar, 0);
	if (!uart.port.membase)
		return -ENOMEM;

	if (mid->board->setup) {
		ret = mid->board->setup(mid, &uart.port);
		if (ret)
			return ret;
	}

	ret = mid8250_dma_setup(mid, &uart);
	if (ret)
		goto err;

	ret = serial8250_register_8250_port(&uart);
	if (ret < 0)
		goto err;

	mid->line = ret;

	pci_set_drvdata(pdev, mid);
	return 0;
err:
	if (mid->board->exit)
		mid->board->exit(mid);
	return ret;
}
