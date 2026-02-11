cstate_pmu_event_init(struct perf_event *event)
{
	u64 cfg = event->attr.config;
	int ret = 0;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;


	if (event->attr.exclude_user   ||
	    event->attr.exclude_kernel ||
	    event->attr.exclude_hv     ||
	    event->attr.exclude_idle   ||
	    event->attr.exclude_host   ||
	    event->attr.exclude_guest  ||
	    event->attr.sample_period)
		return -EINVAL;

	if (event->pmu == &cstate_core_pmu) {
		if (cfg >= PERF_CSTATE_CORE_EVENT_MAX)
			return -EINVAL;
		if (!core_msr[cfg].attr)
			return -EINVAL;
		event->hw.event_base = core_msr[cfg].msr;
	} else if (event->pmu == &cstate_pkg_pmu) {
		if (cfg >= PERF_CSTATE_PKG_EVENT_MAX)
			return -EINVAL;
		if (!pkg_msr[cfg].attr)
			return -EINVAL;
		event->hw.event_base = pkg_msr[cfg].msr;
	} else
		return -ENOENT;


	event->hw.config = cfg;
	event->hw.idx = -1;

	return ret;
}
