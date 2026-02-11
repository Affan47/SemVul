atmel_spi_lock(struct atmel_spi *as) __acquires(&as->lock)
{
	spin_lock_irqsave(&as->lock, as->flags);
}
