hdhomerun_debug_flush(struct hdhomerun_debug_t *dbg, uint64_t timeout)
{
	if (!dbg) {
		return;
	}

	timeout = getcurrenttime() + timeout;

	while (getcurrenttime() < timeout) {
		pthread_mutex_lock(&dbg->queue_lock);
		struct hdhomerun_debug_message_t *message = dbg->queue_tail;
		pthread_mutex_unlock(&dbg->queue_lock);

		if (!message) {
			return;
		}

		msleep_approx(10);
	}
}
