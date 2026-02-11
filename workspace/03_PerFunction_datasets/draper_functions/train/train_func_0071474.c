__db_s_next(sdbpp, txn)
	DB **sdbpp;
	DB_TXN *txn;
{
	DB *sdbp, *pdbp, *closeme;
	ENV *env;
	int ret;


	sdbp = *sdbpp;
	pdbp = sdbp->s_primary;
	env = pdbp->env;
	closeme = NULL;

	MUTEX_LOCK(env, pdbp->mutex);
	DB_ASSERT(env, sdbp->s_refcnt != 0);
	if (--sdbp->s_refcnt == 0) {
		LIST_REMOVE(sdbp, s_links);
		closeme = sdbp;
	}
	sdbp = LIST_NEXT(sdbp, s_links);
	if (sdbp != NULL)
		sdbp->s_refcnt++;
	MUTEX_UNLOCK(env, pdbp->mutex);

	*sdbpp = sdbp;


	if (closeme == NULL)
		ret = 0;
	else
		ret = __db_close(closeme, txn, 0);

	return (ret);
}
