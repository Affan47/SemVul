perf_sched_restore_state(struct perf_sched *sched)
{
	if (!sched->saved_states)
		return false;

	sched->saved_states--;
	sched->state = sched->saved[sched->saved_states];


	clear_bit(sched->state.counter++, sched->state.used);

	return true;
}
