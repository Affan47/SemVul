add_timer_on(struct timer_list *timer, int cpu)
{
	struct tvec_base *new_base = per_cpu_ptr(&tvec_bases, cpu);
	struct tvec_base *base;
	unsigned long flags;

	timer_stats_timer_set_start_info(timer);
	BUG_ON(timer_pending(timer) || !timer->function);


	base = lock_timer_base(timer, &flags);
	if (base != new_base) {
		timer->flags |= TIMER_MIGRATING;

		spin_unlock(&base->lock);
		base = new_base;
		spin_lock(&base->lock);
		WRITE_ONCE(timer->flags,
			   (timer->flags & ~TIMER_BASEMASK) | cpu);
	}

	debug_activate(timer, timer->expires);
	internal_add_timer(base, timer);
	spin_unlock_irqrestore(&base->lock, flags);
}
