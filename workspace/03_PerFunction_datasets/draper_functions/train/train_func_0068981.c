clockevents_program_min_delta(struct clock_event_device *dev)
{
	unsigned long long clc;
	int64_t delta;
	int i;

	for (i = 0;;) {
		delta = dev->min_delta_ns;
		dev->next_event = ktime_add_ns(ktime_get(), delta);

		if (clockevent_state_shutdown(dev))
			return 0;

		dev->retries++;
		clc = ((unsigned long long) delta * dev->mult) >> dev->shift;
		if (dev->set_next_event((unsigned long) clc, dev) == 0)
			return 0;

		if (++i > 2) {


			if (clockevents_increase_min_delta(dev))
				return -ETIME;
			i = 0;
		}
	}
}
