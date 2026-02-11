__db_vrfy_pgset(env, ip, pgsize, dbpp)
	ENV *env;
	DB_THREAD_INFO *ip;
	u_int32_t pgsize;
	DB **dbpp;
{
	DB *dbp;
	int ret;

	if ((ret = __db_create_internal(&dbp, env, 0)) != 0)
		return (ret);
	if ((ret = __db_set_pagesize(dbp, pgsize)) != 0)
		goto err;


	if (TXN_ON(env) &&
	    (ret = __db_set_flags(dbp, DB_TXN_NOT_DURABLE)) != 0)
		goto err;
	if ((ret = __db_open(dbp, ip,
	    NULL, NULL, NULL, DB_BTREE, DB_CREATE, 0600, PGNO_BASE_MD)) == 0)
		*dbpp = dbp;
	else
err:		(void)__db_close(dbp, NULL, 0);

	return (ret);
}
