validate_event(struct perf_event *event)
{
	struct cpu_hw_events *fake_cpuc;
	struct event_constraint *c;
	int ret = 0;

	fake_cpuc = allocate_fake_cpuc();
	if (IS_ERR(fake_cpuc))
		return PTR_ERR(fake_cpuc);

	c = x86_pmu.get_event_constraints(fake_cpuc, -1, event);

	if (!c || !c->weight)
		ret = -EINVAL;

	if (x86_pmu.put_event_constraints)
		x86_pmu.put_event_constraints(fake_cpuc, event);

	free_fake_cpuc(fake_cpuc);

	return ret;
}
