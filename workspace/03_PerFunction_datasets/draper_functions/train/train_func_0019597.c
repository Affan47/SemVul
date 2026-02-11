rapl_pmu_event_stop(struct perf_event *event, int mode)
{
	struct rapl_pmu *pmu = __this_cpu_read(rapl_pmu);
	struct hw_perf_event *hwc = &event->hw;
	unsigned long flags;

	spin_lock_irqsave(&pmu->lock, flags);


	if (!(hwc->state & PERF_HES_STOPPED)) {
		WARN_ON_ONCE(pmu->n_active <= 0);
		pmu->n_active--;
		if (pmu->n_active == 0)
			rapl_stop_hrtimer(pmu);

		list_del(&event->active_entry);

		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;
	}


	if ((mode & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {


		rapl_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	}

	spin_unlock_irqrestore(&pmu->lock, flags);
}
