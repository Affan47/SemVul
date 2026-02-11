perf_iommu_read(struct perf_event *event)
{
	u64 count = 0ULL;
	u64 prev_raw_count = 0ULL;
	u64 delta = 0ULL;
	struct hw_perf_event *hwc = &event->hw;
	pr_debug("perf: amd_iommu:perf_iommu_read\n");

	amd_iommu_pc_get_set_reg_val(_GET_DEVID(event),
				_GET_BANK(event), _GET_CNTR(event),
				IOMMU_PC_COUNTER_REG, &count, false);


	count &= 0xFFFFFFFFFFFFULL;

	prev_raw_count =  local64_read(&hwc->prev_count);
	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
					count) != prev_raw_count)
		return;


	delta = (count << COUNTER_SHIFT) - (prev_raw_count << COUNTER_SHIFT);
	delta >>= COUNTER_SHIFT;
	local64_add(delta, &event->count);

}
