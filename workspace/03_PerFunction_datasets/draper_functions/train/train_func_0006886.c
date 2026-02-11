uncore_pmu_event_stop(struct perf_event *event, int flags)
{
	struct intel_uncore_box *box = uncore_event_to_box(event);
	struct hw_perf_event *hwc = &event->hw;

	if (__test_and_clear_bit(hwc->idx, box->active_mask)) {
		uncore_disable_event(box, event);
		box->n_active--;
		box->events[hwc->idx] = NULL;
		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;

		if (box->n_active == 0) {
			uncore_disable_box(box);
			uncore_pmu_cancel_hrtimer(box);
		}
	}

	if ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {


		uncore_perf_event_update(box, event);
		hwc->state |= PERF_HES_UPTODATE;
	}
}
