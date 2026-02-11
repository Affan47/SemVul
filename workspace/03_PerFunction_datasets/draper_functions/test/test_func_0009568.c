remove_from_logsync(struct metapage *mp)
{
	struct jfs_log *log = mp->log;
	unsigned long flags;


	if (!log)
		return;

	LOGSYNC_LOCK(log, flags);
	if (mp->lsn) {
		mp->log = NULL;
		mp->lsn = 0;
		mp->clsn = 0;
		log->count--;
		list_del(&mp->synclist);
	}
	LOGSYNC_UNLOCK(log, flags);
}
