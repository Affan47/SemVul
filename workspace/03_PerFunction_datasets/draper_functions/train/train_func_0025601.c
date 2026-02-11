__txn_record_fname(env, txn, fname)
	ENV *env;
	DB_TXN *txn;
	FNAME *fname;
{
	DB_LOG *dblp;
	DB_TXNMGR *mgr;
	TXN_DETAIL *td;
	roff_t fname_off;
	roff_t *np, *ldbs;
	u_int32_t i;
	int ret;

	if ((td = txn->td) == NULL)
		return (0);
	mgr = env->tx_handle;
	dblp = env->lg_handle;
	fname_off = R_OFFSET(&dblp->reginfo, fname);


	ldbs = R_ADDR(&mgr->reginfo, td->log_dbs);
	for (i = 0, np = ldbs; i < td->nlog_dbs; i++, np++)
		if (*np == fname_off)
			return (0);

	if (td->nlog_slots <= td->nlog_dbs) {
		TXN_SYSTEM_LOCK(env);
		if ((ret = __env_alloc(&mgr->reginfo,
		    sizeof(roff_t) * (td->nlog_slots << 1), &np)) != 0) {
			TXN_SYSTEM_UNLOCK(env);
			return (ret);
		}

		memcpy(np, ldbs, td->nlog_dbs * sizeof(roff_t));
		if (td->nlog_slots > TXN_NSLOTS)
			__env_alloc_free(&mgr->reginfo, ldbs);

		TXN_SYSTEM_UNLOCK(env);
		td->log_dbs = R_OFFSET(&mgr->reginfo, np);
		ldbs = np;
		td->nlog_slots = td->nlog_slots << 1;
	}

	ldbs[td->nlog_dbs] = fname_off;
	td->nlog_dbs++;
	fname->txn_ref++;

	return (0);
}
