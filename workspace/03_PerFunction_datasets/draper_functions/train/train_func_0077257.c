dwapb_irq_enable(struct irq_data *d)
{
	struct irq_chip_generic *igc = irq_data_get_irq_chip_data(d);
	struct dwapb_gpio *gpio = igc->private;
	struct bgpio_chip *bgc = &gpio->ports[0].bgc;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&bgc->lock, flags);
	val = dwapb_read(gpio, GPIO_INTEN);
	val |= BIT(d->hwirq);
	dwapb_write(gpio, GPIO_INTEN, val);
	spin_unlock_irqrestore(&bgc->lock, flags);
}
