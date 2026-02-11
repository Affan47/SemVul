ack_ticks(struct pthread_timer *timer, unsigned int quantity)
{
	int pending_ticks = timer->pending_ticks;

	ast_assert(quantity);

	if (quantity > pending_ticks) {
		quantity = pending_ticks;
	}

	if (!quantity) {
		return;
	}

	timer->pending_ticks -= quantity;

	if ((0 == timer->pending_ticks) && !timer->continuous) {
		unsignal_pipe(timer);
	}
}
