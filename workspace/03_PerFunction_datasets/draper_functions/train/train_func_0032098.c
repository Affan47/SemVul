timbgpio_to_irq(struct gpio_chip *gpio, unsigned offset)
{
	struct timbgpio *tgpio = container_of(gpio, struct timbgpio, gpio);

	if (tgpio->irq_base <= 0)
		return -EINVAL;

	return tgpio->irq_base + offset;
}
