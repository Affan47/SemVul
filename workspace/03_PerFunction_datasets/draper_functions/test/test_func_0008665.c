select_bad_process(struct oom_control *oc,
		unsigned int *ppoints, unsigned long totalpages)
{
	struct task_struct *g, *p;
	struct task_struct *chosen = NULL;
	unsigned long chosen_points = 0;

	rcu_read_lock();
	for_each_process_thread(g, p) {
		unsigned int points;

		switch (oom_scan_process_thread(oc, p, totalpages)) {
		case OOM_SCAN_SELECT:
			chosen = p;
			chosen_points = ULONG_MAX;

		case OOM_SCAN_CONTINUE:
			continue;
		case OOM_SCAN_ABORT:
			rcu_read_unlock();
			return (struct task_struct *)(-1UL);
		case OOM_SCAN_OK:
			break;
		};
		points = oom_badness(p, NULL, oc->nodemask, totalpages);
		if (!points || points < chosen_points)
			continue;

		if (points == chosen_points && thread_group_leader(chosen))
			continue;

		chosen = p;
		chosen_points = points;
	}
	if (chosen)
		get_task_struct(chosen);
	rcu_read_unlock();

	*ppoints = chosen_points * 1000 / totalpages;
	return chosen;
}
