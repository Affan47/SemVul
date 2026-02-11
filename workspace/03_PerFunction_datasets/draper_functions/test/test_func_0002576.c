max732x_irq_handler(int irq, void *devid)
{
	struct max732x_chip *chip = devid;
	uint8_t pending;
	uint8_t level;

	pending = max732x_irq_pending(chip);

	if (!pending)
		return IRQ_HANDLED;

	do {
		level = __ffs(pending);
		handle_nested_irq(irq_find_mapping(chip->gpio_chip.irqdomain,
						   level));

		pending &= ~(1 << level);
	} while (pending);

	return IRQ_HANDLED;
}
