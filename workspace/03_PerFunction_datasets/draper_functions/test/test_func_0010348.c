r5l_wake_reclaim(struct r5l_log *log, sector_t space)
{
	unsigned long target;
	unsigned long new = (unsigned long)space;

	do {
		target = log->reclaim_target;
		if (new < target)
			return;
	} while (cmpxchg(&log->reclaim_target, target, new) != target);
	md_wakeup_thread(log->reclaim_thread);
}
