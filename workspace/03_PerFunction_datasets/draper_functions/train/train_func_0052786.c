intel_pmu_enable_event(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (unlikely(hwc->idx == INTEL_PMC_IDX_FIXED_BTS)) {
		if (!__this_cpu_read(cpu_hw_events.enabled))
			return;

		intel_pmu_enable_bts(hwc->config);
		return;
	}


	if (needs_branch_stack(event))
		intel_pmu_lbr_enable(event);

	if (event->attr.exclude_host)
		cpuc->intel_ctrl_guest_mask |= (1ull << hwc->idx);
	if (event->attr.exclude_guest)
		cpuc->intel_ctrl_host_mask |= (1ull << hwc->idx);

	if (unlikely(event_is_checkpointed(event)))
		cpuc->intel_cp_status |= (1ull << hwc->idx);

	if (unlikely(hwc->config_base == MSR_ARCH_PERFMON_FIXED_CTR_CTRL)) {
		intel_pmu_enable_fixed(hwc);
		return;
	}

	if (unlikely(event->attr.precise_ip))
		intel_pmu_pebs_enable(event);

	__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
}
