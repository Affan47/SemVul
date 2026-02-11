intel_find_fixed_event(int idx)
{
	if (idx >= ARRAY_SIZE(fixed_pmc_events))
		return PERF_COUNT_HW_MAX;

	return intel_arch_events[fixed_pmc_events[idx]].event_type;
}
