select_estimate_accuracy(struct timespec *tv)
{
	unsigned long ret;
	struct timespec now;


	if (rt_task(current))
		return 0;

	ktime_get_ts(&now);
	now = timespec_sub(*tv, now);
	ret = __estimate_accuracy(&now);
	if (ret < current->timer_slack_ns)
		return current->timer_slack_ns;
	return ret;
}
