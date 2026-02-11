rapl_event_update(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 prev_raw_count, new_raw_count;
	s64 delta, sdelta;
	int shift = RAPL_CNTR_WIDTH;

again:
	prev_raw_count = local64_read(&hwc->prev_count);
	rdmsrl(event->hw.event_base, new_raw_count);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count) {
		cpu_relax();
		goto again;
	}


	delta = (new_raw_count << shift) - (prev_raw_count << shift);
	delta >>= shift;

	sdelta = rapl_scale(delta, event->hw.config);

	local64_add(sdelta, &event->count);

	return new_raw_count;
}
