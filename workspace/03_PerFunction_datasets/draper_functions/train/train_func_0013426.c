spi_start_queue(struct spi_master *master)
{
	unsigned long flags;

	spin_lock_irqsave(&master->queue_lock, flags);

	if (master->running || master->busy) {
		spin_unlock_irqrestore(&master->queue_lock, flags);
		return -EBUSY;
	}

	master->running = true;
	master->cur_msg = NULL;
	spin_unlock_irqrestore(&master->queue_lock, flags);

	queue_kthread_work(&master->kworker, &master->pump_messages);

	return 0;
}
