ci_otg_hrtimer_func(struct hrtimer *t)
{
	struct ci_hdrc *ci = container_of(t, struct ci_hdrc, otg_fsm_hrtimer);
	ktime_t	now, *timeout;
	unsigned long   enabled_timer_bits;
	unsigned long   flags;
	enum otg_fsm_timer cur_timer, next_timer = NUM_OTG_FSM_TIMERS;
	int ret = -EINVAL;

	spin_lock_irqsave(&ci->lock, flags);
	enabled_timer_bits = ci->enabled_otg_timer_bits;
	ci->next_otg_timer = NUM_OTG_FSM_TIMERS;

	now = ktime_get();
	for_each_set_bit(cur_timer, &enabled_timer_bits, NUM_OTG_FSM_TIMERS) {
		if (now.tv64 >= ci->hr_timeouts[cur_timer].tv64) {
			ci->enabled_otg_timer_bits &= ~(1 << cur_timer);
			if (otg_timer_handlers[cur_timer])
				ret = otg_timer_handlers[cur_timer](ci);
		} else {
			if ((next_timer == NUM_OTG_FSM_TIMERS) ||
				(ci->hr_timeouts[cur_timer].tv64 <
					ci->hr_timeouts[next_timer].tv64))
				next_timer = cur_timer;
		}
	}

	if (next_timer < NUM_OTG_FSM_TIMERS) {
		timeout = &ci->hr_timeouts[next_timer];
		hrtimer_start_range_ns(&ci->otg_fsm_hrtimer, *timeout,
					NSEC_PER_MSEC, HRTIMER_MODE_ABS);
		ci->next_otg_timer = next_timer;
	}
	spin_unlock_irqrestore(&ci->lock, flags);

	if (!ret)
		ci_otg_queue_work(ci);

	return HRTIMER_NORESTART;
}
