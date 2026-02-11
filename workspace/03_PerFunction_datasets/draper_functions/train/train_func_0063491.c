__log_stat(env, statp, flags)
	ENV *env;
	DB_LOG_STAT **statp;
	u_int32_t flags;
{
	DB_LOG *dblp;
	DB_LOG_STAT *stats;
	LOG *lp;
	int ret;

	*statp = NULL;

	dblp = env->lg_handle;
	lp = dblp->reginfo.primary;

	if ((ret = __os_umalloc(env, sizeof(DB_LOG_STAT), &stats)) != 0)
		return (ret);


	LOG_SYSTEM_LOCK(env);
	*stats = lp->stat;
	if (LF_ISSET(DB_STAT_CLEAR))
		memset(&lp->stat, 0, sizeof(lp->stat));

	stats->st_magic = lp->persist.magic;
	stats->st_version = lp->persist.version;
	stats->st_mode = lp->filemode;
	stats->st_lg_bsize = lp->buffer_size;
	stats->st_lg_size = lp->log_nsize;

	__mutex_set_wait_info(env, lp->mtx_region,
	    &stats->st_region_wait, &stats->st_region_nowait);
	if (LF_ISSET(DB_STAT_CLEAR | DB_STAT_SUBSYSTEM) == DB_STAT_CLEAR)
		__mutex_clear(env, lp->mtx_region);
	stats->st_regsize = dblp->reginfo.rp->size;

	stats->st_cur_file = lp->lsn.file;
	stats->st_cur_offset = lp->lsn.offset;
	stats->st_disk_file = lp->s_lsn.file;
	stats->st_disk_offset = lp->s_lsn.offset;

	LOG_SYSTEM_UNLOCK(env);

	*statp = stats;
	return (0);
}
