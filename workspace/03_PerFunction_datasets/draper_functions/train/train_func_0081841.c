hpi_clear_bits(struct c67x00_device *dev, u16 reg, u16 mask)
{
	u16 value;
	unsigned long flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	value = hpi_read_word_nolock(dev, reg);
	hpi_write_word_nolock(dev, reg, value & ~mask);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);
}
