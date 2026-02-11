__dbreg_get_id(dbp, txn, idp)
	DB *dbp;
	DB_TXN *txn;
	int32_t *idp;
{
	DB_LOG *dblp;
	ENV *env;
	FNAME *fnp;
	LOG *lp;
	int32_t id;
	int ret;

	env = dbp->env;
	dblp = env->lg_handle;
	lp = dblp->reginfo.primary;
	fnp = dbp->log_filename;


	if ((ret = __dbreg_pop_id(env, &id)) != 0)
		goto err;


	if (id == DB_LOGFILEID_INVALID)
		id = lp->fid_max++;


	if (!F_ISSET(dbp, DB_AM_NOT_DURABLE))
		F_SET(fnp, DB_FNAME_DURABLE);


	SH_TAILQ_INSERT_HEAD(&lp->fq, fnp, q, __fname);


	DB_ASSERT(env, !F_ISSET(dbp, DB_AM_RECOVER));

	if ((ret = __dbreg_log_id(dbp, txn, id, 0)) != 0)
		goto err;


	fnp->create_txnid = TXN_INVALID;

	DB_ASSERT(env, dbp->type == fnp->s_type);
	DB_ASSERT(env, dbp->meta_pgno == fnp->meta_pgno);

	if ((ret = __dbreg_add_dbentry(env, dblp, dbp, id)) != 0)
		goto err;


err:
	if (ret != 0 && id != DB_LOGFILEID_INVALID) {
		(void)__dbreg_revoke_id(dbp, 1, id);
		id = DB_LOGFILEID_INVALID;
	}
	*idp = id;
	return (ret);
}
