intel_cqm_event_destroy(struct perf_event *event)
{
	struct perf_event *group_other = NULL;
	unsigned long flags;

	mutex_lock(&cache_mutex);


	raw_spin_lock_irqsave(&cache_lock, flags);


	if (!list_empty(&event->hw.cqm_group_entry)) {
		group_other = list_first_entry(&event->hw.cqm_group_entry,
					       struct perf_event,
					       hw.cqm_group_entry);
		list_del(&event->hw.cqm_group_entry);
	}


	if (cqm_group_leader(event)) {


		if (group_other) {
			list_replace(&event->hw.cqm_groups_entry,
				     &group_other->hw.cqm_groups_entry);
		} else {
			u32 rmid = event->hw.cqm_rmid;

			if (__rmid_valid(rmid))
				__put_rmid(rmid);
			list_del(&event->hw.cqm_groups_entry);
		}
	}

	raw_spin_unlock_irqrestore(&cache_lock, flags);


	if (mbm_enabled && list_empty(&cache_groups))
		mbm_stop_timers();

	mutex_unlock(&cache_mutex);
}
