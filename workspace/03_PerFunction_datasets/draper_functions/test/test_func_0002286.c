max3100_shutdown(struct uart_port *port)
{
	struct max3100_port *s = container_of(port,
					      struct max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	if (s->suspending)
		return;

	s->force_end_work = 1;

	if (s->poll_time > 0)
		del_timer_sync(&s->timer);

	if (s->workqueue) {
		flush_workqueue(s->workqueue);
		destroy_workqueue(s->workqueue);
		s->workqueue = NULL;
	}
	if (s->irq)
		free_irq(s->irq, s);


	if (s->max3100_hw_suspend)
		s->max3100_hw_suspend(1);
	else  {
		u16 tx, rx;

		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sr(s, tx, &rx);
	}
}
