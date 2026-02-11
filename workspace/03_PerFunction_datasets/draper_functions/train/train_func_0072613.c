__txn_recycle_id(env, locked)
	ENV *env;
	int locked;
{
	DB_LSN null_lsn;
	DB_TXNMGR *mgr;
	DB_TXNREGION *region;
	TXN_DETAIL *td;
	u_int32_t *ids;
	int nids, ret;

	mgr = env->tx_handle;
	region = mgr->reginfo.primary;

	if ((ret = __os_malloc(env,
	    sizeof(u_int32_t) * region->curtxns, &ids)) != 0) {
		__db_errx(env, DB_STR("4523",
		    "Unable to allocate transaction recycle buffer"));
		return (ret);
	}
	nids = 0;
	SH_TAILQ_FOREACH(td, &region->active_txn, links, __txn_detail)
		ids[nids++] = td->txnid;
	region->last_txnid = TXN_MINIMUM - 1;
	region->cur_maxid = TXN_MAXIMUM;
	if (nids != 0)
		__db_idspace(ids, nids,
		    &region->last_txnid, &region->cur_maxid);
	__os_free(env, ids);


	if (LOGGING_ON(env)) {
		if (locked)
			TXN_SYSTEM_UNLOCK(env);
		ret = __txn_recycle_log(env, NULL, &null_lsn,
		     0, region->last_txnid + 1, region->cur_maxid);

		if (locked && ret != 0)
			TXN_SYSTEM_LOCK(env);
	}

	return (ret);
}
