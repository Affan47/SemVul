timbgpio_irq_disable(struct irq_data *d)
{
	struct timbgpio *tgpio = irq_data_get_irq_chip_data(d);
	int offset = d->irq - tgpio->irq_base;
	unsigned long flags;

	spin_lock_irqsave(&tgpio->lock, flags);
	tgpio->last_ier &= ~(1UL << offset);
	iowrite32(tgpio->last_ier, tgpio->membase + TGPIO_IER);
	spin_unlock_irqrestore(&tgpio->lock, flags);
}
