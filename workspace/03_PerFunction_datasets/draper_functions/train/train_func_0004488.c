lp_irq_enable(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct lp_gpio *lg = container_of(gc, struct lp_gpio, chip);
	u32 hwirq = irqd_to_hwirq(d);
	unsigned long reg = lp_gpio_reg(&lg->chip, hwirq, LP_INT_ENABLE);
	unsigned long flags;

	spin_lock_irqsave(&lg->lock, flags);
	outl(inl(reg) | BIT(hwirq % 32), reg);
	spin_unlock_irqrestore(&lg->lock, flags);
}
