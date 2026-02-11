userspace_postsuspend(struct dm_dirty_log *log)
{
	int r;
	struct log_c *lc = log->context;


	if (lc->integrated_flush && atomic_read(&lc->sched_flush))
		flush_delayed_work(&lc->flush_log_work);

	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_POSTSUSPEND,
				 NULL, 0, NULL, NULL);

	return r;
}
