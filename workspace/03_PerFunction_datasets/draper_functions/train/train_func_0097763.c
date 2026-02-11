validate_group(struct perf_event *event)
{
	struct perf_event *leader = event->group_leader;
	struct cpu_hw_events *fake_cpuc;
	int ret = -EINVAL, n;

	fake_cpuc = allocate_fake_cpuc();
	if (IS_ERR(fake_cpuc))
		return PTR_ERR(fake_cpuc);


	n = collect_events(fake_cpuc, leader, true);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = n;
	n = collect_events(fake_cpuc, event, false);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = n;

	ret = x86_pmu.schedule_events(fake_cpuc, n, NULL);

out:
	free_fake_cpuc(fake_cpuc);
	return ret;
}
