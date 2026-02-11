pulse_queue_check_window(struct pri_detector *pde)
{
	u64 min_valid_ts;
	struct pulse_elem *p;


	if (pde->count < 2)
		return;

	if (pde->last_ts <= pde->window_size)
		return;

	min_valid_ts = pde->last_ts - pde->window_size;
	while ((p = pulse_queue_get_tail(pde)) != NULL) {
		if (p->ts >= min_valid_ts)
			return;
		pulse_queue_dequeue(pde);
	}
}
