max310x_gpio_direction_output(struct gpio_chip *chip,
					 unsigned offset, int value)
{
	struct max310x_port *s = container_of(chip, struct max310x_port, gpio);
	struct uart_port *port = &s->p[offset / 4].port;

	max310x_port_update(port, MAX310X_GPIODATA_REG, 1 << (offset % 4),
			    value ? 1 << (offset % 4) : 0);
	max310x_port_update(port, MAX310X_GPIOCFG_REG, 1 << (offset % 4),
			    1 << (offset % 4));

	return 0;
}
