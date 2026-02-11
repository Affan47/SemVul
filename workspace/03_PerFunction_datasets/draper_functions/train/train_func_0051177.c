sc16is7xx_init(void)
{
	int ret;

	ret = uart_register_driver(&sc16is7xx_uart);
	if (ret) {
		pr_err("Registering UART driver failed\n");
		return ret;
	}

#ifdef CONFIG_SERIAL_SC16IS7XX_I2C
	ret = i2c_add_driver(&sc16is7xx_i2c_uart_driver);
	if (ret < 0) {
		pr_err("failed to init sc16is7xx i2c --> %d\n", ret);
		return ret;
	}
#endif

#ifdef CONFIG_SERIAL_SC16IS7XX_SPI
	ret = spi_register_driver(&sc16is7xx_spi_uart_driver);
	if (ret < 0) {
		pr_err("failed to init sc16is7xx spi --> %d\n", ret);
		return ret;
	}
#endif
	return ret;
}
