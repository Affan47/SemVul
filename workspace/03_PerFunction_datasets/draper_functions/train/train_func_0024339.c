lpc18xx_gpio_direction(struct gpio_chip *chip, unsigned offset,
				  bool out)
{
	struct lpc18xx_gpio_chip *gc = to_lpc18xx_gpio(chip);
	unsigned long flags;
	u32 port, pin, dir;

	port = offset / LPC18XX_PINS_PER_PORT;
	pin  = offset % LPC18XX_PINS_PER_PORT;

	spin_lock_irqsave(&gc->lock, flags);
	dir = readl(gc->base + LPC18XX_REG_DIR(port));
	if (out)
		dir |= BIT(pin);
	else
		dir &= ~BIT(pin);
	writel(dir, gc->base + LPC18XX_REG_DIR(port));
	spin_unlock_irqrestore(&gc->lock, flags);

	return 0;
}
