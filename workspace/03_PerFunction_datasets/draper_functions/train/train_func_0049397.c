max3100_irq(int irqno, void *dev_id)
{
	struct max3100_port *s = dev_id;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	max3100_dowork(s);
	return IRQ_HANDLED;
}
