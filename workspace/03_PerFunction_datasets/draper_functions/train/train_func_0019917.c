nhm_uncore_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	if (hwc->idx < UNCORE_PMC_IDX_FIXED)
		wrmsrl(hwc->config_base, hwc->config | SNB_UNC_CTL_EN);
	else
		wrmsrl(hwc->config_base, NHM_UNC_FIXED_CTR_CTL_EN);
}
