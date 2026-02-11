wd_expired(cqueue_t *cq, void *arg)
{
	watchdog_t *wd = arg;

	watchdog_check(wd);

	wd->ev = NULL;


	if (0 == wd->last_kick) {
		wd_trigger(wd);
	} else {
		time_t now = tm_time();
		time_delta_t elapsed = delta_time(now, wd->last_kick);


		if (elapsed >= wd->period) {
			wd_trigger(wd);
		} else {
			time_delta_t delay = wd->period - elapsed;
			wd->ev = cq_insert(cq, delay * 1000, wd_expired, wd);
		}
	}
}
