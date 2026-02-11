intel_cqm_event_init(struct perf_event *event)
{
	struct perf_event *group = NULL;
	bool rotate = false;
	unsigned long flags;

	if (event->attr.type != intel_cqm_pmu.type)
		return -ENOENT;

	if ((event->attr.config < QOS_L3_OCCUP_EVENT_ID) ||
	     (event->attr.config > QOS_MBM_LOCAL_EVENT_ID))
		return -EINVAL;


	if (event->attr.exclude_user   ||
	    event->attr.exclude_kernel ||
	    event->attr.exclude_hv     ||
	    event->attr.exclude_idle   ||
	    event->attr.exclude_host   ||
	    event->attr.exclude_guest  ||
	    event->attr.sample_period)
		return -EINVAL;

	INIT_LIST_HEAD(&event->hw.cqm_group_entry);
	INIT_LIST_HEAD(&event->hw.cqm_groups_entry);

	event->destroy = intel_cqm_event_destroy;

	mutex_lock(&cache_mutex);


	if (mbm_enabled && list_empty(&cache_groups))
		mbm_start_timers();


	intel_cqm_setup_event(event, &group);


	raw_spin_lock_irqsave(&cache_lock, flags);

	if (group) {
		list_add_tail(&event->hw.cqm_group_entry,
			      &group->hw.cqm_group_entry);
	} else {
		list_add_tail(&event->hw.cqm_groups_entry,
			      &cache_groups);


		if (!__rmid_valid(event->hw.cqm_rmid))
			rotate = true;
	}

	raw_spin_unlock_irqrestore(&cache_lock, flags);
	mutex_unlock(&cache_mutex);

	if (rotate)
		schedule_delayed_work(&intel_cqm_rmid_work, 0);

	return 0;
}
