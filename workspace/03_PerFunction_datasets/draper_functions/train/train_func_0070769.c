__seq_stat(seq, spp, flags)
	DB_SEQUENCE *seq;
	DB_SEQUENCE_STAT **spp;
	u_int32_t flags;
{
	DB *dbp;
	DBT data;
	DB_SEQUENCE_STAT *sp;
	DB_SEQ_RECORD record;
	DB_THREAD_INFO *ip;
	ENV *env;
	int handle_check, ret, t_ret;

	dbp = seq->seq_dbp;
	env = dbp->env;

	SEQ_ILLEGAL_BEFORE_OPEN(seq, "DB_SEQUENCE->stat");

	switch (flags) {
	case DB_STAT_CLEAR:
	case DB_STAT_ALL:
	case 0:
		break;
	default:
		return (__db_ferr(env, "DB_SEQUENCE->stat", 0));
	}

	ENV_ENTER(env, ip);


	handle_check = IS_ENV_REPLICATED(env);
	if (handle_check && (ret = __db_rep_enter(dbp, 1, 0, 0)) != 0) {
		handle_check = 0;
		goto err;
	}


	if ((ret = __os_umalloc(env, sizeof(*sp), &sp)) != 0)
		goto err;
	memset(sp, 0, sizeof(*sp));

	if (seq->mtx_seq != MUTEX_INVALID) {
		__mutex_set_wait_info(
		    env, seq->mtx_seq, &sp->st_wait, &sp->st_nowait);

		if (LF_ISSET(DB_STAT_CLEAR))
			__mutex_clear(env, seq->mtx_seq);
	}
	memset(&data, 0, sizeof(data));
	data.data = &record;
	data.ulen = sizeof(record);
	data.flags = DB_DBT_USERMEM;
retry:	if ((ret = __db_get(dbp, ip, NULL, &seq->seq_key, &data, 0)) != 0) {
		if (ret == DB_BUFFER_SMALL &&
		    data.size > sizeof(seq->seq_record)) {
			if ((ret = __os_malloc(env,
			    data.size, &data.data)) != 0)
				goto err;
			data.ulen = data.size;
			goto retry;
		}
		goto err;
	}

	if (data.data != &record)
		memcpy(&record, data.data, sizeof(record));
	sp->st_current = record.seq_value;
	sp->st_value = seq->seq_record.seq_value;
	sp->st_last_value = seq->seq_last_value;
	sp->st_min = seq->seq_record.seq_min;
	sp->st_max = seq->seq_record.seq_max;
	sp->st_cache_size = seq->seq_cache_size;
	sp->st_flags = seq->seq_record.flags;

	*spp = sp;
	if (data.data != &record)
		__os_free(env, data.data);


err:	if (handle_check && (t_ret = __env_db_rep_exit(env)) != 0 && ret == 0)
		ret = t_ret;
	ENV_LEAVE(env, ip);
	return (ret);
}
