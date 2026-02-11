lp_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct lp_gpio *lg = container_of(chip, struct lp_gpio, chip);
	unsigned long reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	unsigned long flags;

	spin_lock_irqsave(&lg->lock, flags);

	if (value)
		outl(inl(reg) | OUT_LVL_BIT, reg);
	else
		outl(inl(reg) & ~OUT_LVL_BIT, reg);

	spin_unlock_irqrestore(&lg->lock, flags);
}
