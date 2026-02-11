__log_vtruncate(env, lsn, ckplsn, trunclsn)
	ENV *env;
	DB_LSN *lsn, *ckplsn, *trunclsn;
{
	DBT log_dbt;
	DB_LOG *dblp;
	DB_LOGC *logc;
	LOG *lp;
	u_int32_t bytes, len;
	size_t offset;
	int ret, t_ret;


	if ((ret = __log_cursor(env, &logc)) != 0)
		return (ret);
	memset(&log_dbt, 0, sizeof(log_dbt));
	ret = __logc_get(logc, lsn, &log_dbt, DB_SET);
	len = logc->len;
	if ((t_ret = __logc_close(logc)) != 0 && ret == 0)
		ret = t_ret;
	if (ret != 0)
		return (ret);


	dblp = env->lg_handle;
	lp = (LOG *)dblp->reginfo.primary;

	LOG_SYSTEM_LOCK(env);


	if ((ret = __log_flush_int(dblp, NULL, 0)) != 0)
		goto err;

	lp->lsn = *lsn;
	lp->len = len;
	lp->lsn.offset += lp->len;

	offset = lp->b_off;
	if (lp->db_log_inmemory && (ret =
	    __log_inmem_lsnoff(dblp, &lp->lsn, &offset)) != 0) {
			lp->b_off = (db_size_t)offset;
			goto err;
	}
	lp->b_off = (db_size_t)offset;


	DB_ASSERT(env, lp->lsn.file >= ckplsn->file);
	bytes = 0;
	if (ckplsn->file != lp->lsn.file) {
		bytes = lp->log_size - ckplsn->offset;
		if (lp->lsn.file > ckplsn->file + 1)
			bytes += lp->log_size *
			    ((lp->lsn.file - ckplsn->file) - 1);
		bytes += lp->lsn.offset;
	} else
		bytes = lp->lsn.offset - ckplsn->offset;

	lp->stat.st_wc_mbytes += bytes / MEGABYTE;
	lp->stat.st_wc_bytes += bytes % MEGABYTE;


	MUTEX_LOCK(env, lp->mtx_flush);
	if (LOG_COMPARE(&lp->s_lsn, lsn) > 0)
		lp->s_lsn = lp->lsn;
	MUTEX_UNLOCK(env, lp->mtx_flush);


	ZERO_LSN(lp->f_lsn);
	lp->w_off = lp->lsn.offset;

	if (trunclsn != NULL)
		*trunclsn = lp->lsn;


	if ((ret = __log_zero(env, &lp->lsn)) != 0)
		goto err;

err:	LOG_SYSTEM_UNLOCK(env);
	return (ret);
}
