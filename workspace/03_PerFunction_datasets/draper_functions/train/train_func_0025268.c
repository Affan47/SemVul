timbgpio_update_bit(struct gpio_chip *gpio, unsigned index,
	unsigned offset, bool enabled)
{
	struct timbgpio *tgpio = container_of(gpio, struct timbgpio, gpio);
	u32 reg;

	spin_lock(&tgpio->lock);
	reg = ioread32(tgpio->membase + offset);

	if (enabled)
		reg |= (1 << index);
	else
		reg &= ~(1 << index);

	iowrite32(reg, tgpio->membase + offset);
	spin_unlock(&tgpio->lock);

	return 0;
}
