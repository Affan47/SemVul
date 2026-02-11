__txn_set_name(txn, name)
	DB_TXN *txn;
	const char *name;
{
	DB_THREAD_INFO *ip;
	DB_TXNMGR *mgr;
	ENV *env;
	TXN_DETAIL *td;
	size_t len;
	int ret;
	char *p;

	mgr = txn->mgrp;
	env = mgr->env;
	td = txn->td;
	len = strlen(name) + 1;

	if ((ret = __os_realloc(env, len, &txn->name)) != 0)
		return (ret);
	memcpy(txn->name, name, len);

	ENV_ENTER(env, ip);
	TXN_SYSTEM_LOCK(env);
	if (td->name != INVALID_ROFF) {
		__env_alloc_free(
		    &mgr->reginfo, R_ADDR(&mgr->reginfo, td->name));
		td->name = INVALID_ROFF;
	}
	if ((ret = __env_alloc(&mgr->reginfo, len, &p)) != 0) {
		TXN_SYSTEM_UNLOCK(env);
		__db_errx(env, DB_STR("4529",
		    "Unable to allocate memory for transaction name"));

		__os_free(env, txn->name);
		txn->name = NULL;

		ENV_LEAVE(env, ip);
		return (ret);
	}
	TXN_SYSTEM_UNLOCK(env);
	td->name = R_OFFSET(&mgr->reginfo, p);
	memcpy(p, name, len);

#ifdef DIAGNOSTIC


	if (DBENV_LOGGING(env))
		(void)__log_printf(env, txn, "transaction %#lx named %s",
		    (u_long)txn->txnid, name);
#endif

	ENV_LEAVE(env, ip);
	return (0);
}
