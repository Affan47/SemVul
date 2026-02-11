mantis_uart_init(struct mantis_pci *mantis)
{
	struct mantis_hwconfig *config = mantis->hwconfig;
	struct mantis_uart_params params;


	params.baud_rate = config->baud_rate;
	params.parity = config->parity;
	dprintk(MANTIS_INFO, 1, "Initializing UART @ %sbps parity:%s",
		rates[params.baud_rate].string,
		parity[params.parity].string);

	INIT_WORK(&mantis->uart_work, mantis_uart_work);


	mmwrite(mmread(MANTIS_UART_CTL) & 0xffef, MANTIS_UART_CTL);

	mantis_uart_setup(mantis, &params);


	mmwrite((mmread(MANTIS_UART_BAUD) | (config->bytes << 8)), MANTIS_UART_BAUD);


	mmwrite((mmread(MANTIS_UART_CTL) | MANTIS_UART_RXFLUSH), MANTIS_UART_CTL);


	mmwrite(mmread(MANTIS_UART_CTL) | MANTIS_UART_RXINT, MANTIS_UART_CTL);
	mantis_unmask_ints(mantis, MANTIS_INT_IRQ1);

	schedule_work(&mantis->uart_work);
	dprintk(MANTIS_DEBUG, 1, "UART successfully initialized");

	return 0;
}
