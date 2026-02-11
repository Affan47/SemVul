__run_hrtimer(struct hrtimer_cpu_base *cpu_base,
			  struct hrtimer_clock_base *base,
			  struct hrtimer *timer, ktime_t *now)
{
	enum hrtimer_restart (*fn)(struct hrtimer *);
	int restart;

	lockdep_assert_held(&cpu_base->lock);

	debug_deactivate(timer);
	cpu_base->running = timer;


	raw_write_seqcount_barrier(&cpu_base->seq);

	__remove_hrtimer(timer, base, HRTIMER_STATE_INACTIVE, 0);
	timer_stats_account_hrtimer(timer);
	fn = timer->function;


	if (IS_ENABLED(CONFIG_TIME_LOW_RES))
		timer->is_rel = false;


	raw_spin_unlock(&cpu_base->lock);
	trace_hrtimer_expire_entry(timer, now);
	restart = fn(timer);
	trace_hrtimer_expire_exit(timer);
	raw_spin_lock(&cpu_base->lock);


	if (restart != HRTIMER_NORESTART &&
	    !(timer->state & HRTIMER_STATE_ENQUEUED))
		enqueue_hrtimer(timer, base);


	raw_write_seqcount_barrier(&cpu_base->seq);

	WARN_ON_ONCE(cpu_base->running != timer);
	cpu_base->running = NULL;
}
