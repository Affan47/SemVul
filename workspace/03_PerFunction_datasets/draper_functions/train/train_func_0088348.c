adnp_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct adnp *adnp = to_adnp(gc);
	unsigned int reg = d->hwirq >> adnp->reg_shift;
	unsigned int pos = d->hwirq & 7;

	if (type & IRQ_TYPE_EDGE_RISING)
		adnp->irq_rise[reg] |= BIT(pos);
	else
		adnp->irq_rise[reg] &= ~BIT(pos);

	if (type & IRQ_TYPE_EDGE_FALLING)
		adnp->irq_fall[reg] |= BIT(pos);
	else
		adnp->irq_fall[reg] &= ~BIT(pos);

	if (type & IRQ_TYPE_LEVEL_HIGH)
		adnp->irq_high[reg] |= BIT(pos);
	else
		adnp->irq_high[reg] &= ~BIT(pos);

	if (type & IRQ_TYPE_LEVEL_LOW)
		adnp->irq_low[reg] |= BIT(pos);
	else
		adnp->irq_low[reg] &= ~BIT(pos);

	return 0;
}
