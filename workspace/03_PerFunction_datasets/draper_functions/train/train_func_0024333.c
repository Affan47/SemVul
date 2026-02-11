sc16is7xx_gpio_direction_output(struct gpio_chip *chip,
					   unsigned offset, int val)
{
	struct sc16is7xx_port *s = container_of(chip, struct sc16is7xx_port,
						gpio);
	struct uart_port *port = &s->p[0].port;

	sc16is7xx_port_update(port, SC16IS7XX_IOSTATE_REG, BIT(offset),
			      val ? BIT(offset) : 0);
	sc16is7xx_port_update(port, SC16IS7XX_IODIR_REG, BIT(offset),
			      BIT(offset));

	return 0;
}
