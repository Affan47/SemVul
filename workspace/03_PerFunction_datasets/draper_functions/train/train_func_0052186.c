perf_sched_init(struct perf_sched *sched, struct event_constraint **constraints,
			    int num, int wmin, int wmax, int gpmax)
{
	int idx;

	memset(sched, 0, sizeof(*sched));
	sched->max_events	= num;
	sched->max_weight	= wmax;
	sched->max_gp		= gpmax;
	sched->constraints	= constraints;

	for (idx = 0; idx < num; idx++) {
		if (constraints[idx]->weight == wmin)
			break;
	}

	sched->state.event	= idx;
	sched->state.weight	= wmin;
	sched->state.unassigned	= num;
}
