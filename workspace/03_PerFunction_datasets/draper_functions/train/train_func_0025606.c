spi_get_next_queued_message(struct spi_master *master)
{
	struct spi_message *next;
	unsigned long flags;


	spin_lock_irqsave(&master->queue_lock, flags);
	next = list_first_entry_or_null(&master->queue, struct spi_message,
					queue);
	spin_unlock_irqrestore(&master->queue_lock, flags);

	return next;
}
