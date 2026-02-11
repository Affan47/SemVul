detach_if_pending(struct timer_list *timer, struct tvec_base *base,
			     bool clear_pending)
{
	if (!timer_pending(timer))
		return 0;

	detach_timer(timer, clear_pending);
	if (!(timer->flags & TIMER_DEFERRABLE)) {
		base->active_timers--;
		if (timer->expires == base->next_timer)
			base->next_timer = base->timer_jiffies;
	}

	if (!--base->all_timers)
		base->timer_jiffies = jiffies;
	return 1;
}
