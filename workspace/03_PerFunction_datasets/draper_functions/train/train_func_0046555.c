gr_irq(int irq, void *_dev)
{
	struct gr_udc *dev = _dev;

	if (!dev->irq_enabled)
		return IRQ_NONE;

	return IRQ_WAKE_THREAD;
}
