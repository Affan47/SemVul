x86_get_event_constraints(struct cpu_hw_events *cpuc, int idx,
			  struct perf_event *event)
{
	struct event_constraint *c;

	if (x86_pmu.event_constraints) {
		for_each_event_constraint(c, x86_pmu.event_constraints) {
			if ((event->hw.config & c->cmask) == c->code) {
				event->hw.flags |= c->flags;
				return c;
			}
		}
	}

	return &unconstrained;
}
