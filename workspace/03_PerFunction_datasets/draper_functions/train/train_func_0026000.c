retry_step ( struct process *process __unused ) {
	struct retry_timer *timer;
	struct retry_timer *tmp;
	unsigned long now = currticks();
	unsigned long used;

	list_for_each_entry_safe ( timer, tmp, &timers, list ) {
		used = ( now - timer->start );
		if ( used >= timer->timeout )
			timer_expired ( timer );
	}
}
