__db_remove_int(dbp, ip, txn, name, subdb, flags)
	DB *dbp;
	DB_THREAD_INFO *ip;
	DB_TXN *txn;
	const char *name, *subdb;
	u_int32_t flags;
{
	ENV *env;
	int ret;
	char *real_name, *tmpname;

	env = dbp->env;
	real_name = tmpname = NULL;

	if (name == NULL && subdb == NULL) {
		__db_errx(env, DB_STR("0691",
		    "Remove on temporary files invalid"));
		ret = EINVAL;
		goto err;
	}

	if (name == NULL) {
		MAKE_INMEM(dbp);
		real_name = (char *)subdb;
	} else if (subdb != NULL) {
		ret = __db_subdb_remove(dbp, ip, txn, name, subdb, flags);
		goto err;
	}


	if (IS_REAL_TXN(txn)) {
		ret = __db_dbtxn_remove(dbp, ip, txn, name, subdb, DB_APP_DATA);
		goto err;
	}


	if (!F_ISSET(dbp, DB_AM_INMEM) && (ret = __db_appname(env,
	    DB_APP_DATA, name, &dbp->dirname, &real_name)) != 0)
		goto err;


	if (!F_ISSET(dbp, DB_AM_INMEM) && LF_ISSET(DB_FORCE) &&
	    (ret = __db_backup_name(env, real_name, NULL, &tmpname)) == 0)
		(void)__os_unlink(env, tmpname, 0);

	if ((ret = __fop_remove_setup(dbp, NULL, real_name, 0)) != 0)
		goto err;

	if (dbp->db_am_remove != NULL &&
	    (ret = dbp->db_am_remove(dbp, ip, NULL, name, subdb, flags)) != 0)
		goto err;

	if (dbp->db_am_remove == NULL &&
	    (ret = __blob_del_all(dbp, txn, 0)) != 0)
		goto err;

	ret = F_ISSET(dbp, DB_AM_INMEM) ?
	    __db_inmem_remove(dbp, NULL, real_name) :
	    __fop_remove(env,
	    NULL, dbp->fileid, name, &dbp->dirname, DB_APP_DATA,
	    F_ISSET(dbp, DB_AM_NOT_DURABLE) ? DB_LOG_NOT_DURABLE : 0);

err:	if (!F_ISSET(dbp, DB_AM_INMEM) && real_name != NULL)
		__os_free(env, real_name);
	if (tmpname != NULL)
		__os_free(env, tmpname);

	return (ret);
}
