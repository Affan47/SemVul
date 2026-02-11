__db_txnlist_update(env, hp, txnid, status, lsn, ret_status, add_ok)
	ENV *env;
	DB_TXNHEAD *hp;
	u_int32_t txnid, status;
	DB_LSN *lsn;
	u_int32_t *ret_status;
	int add_ok;
{
	DB_TXNLIST *elp;
	int ret;

	if (txnid == 0)
		return (DB_NOTFOUND);

	ret = __db_txnlist_find_internal(env,
	    hp, TXNLIST_TXNID, txnid, &elp, 0, ret_status);

	if (ret == DB_NOTFOUND && add_ok) {
		*ret_status = status;
		return (__db_txnlist_add(env, hp, txnid, status, lsn));
	}
	if (ret != 0)
		return (ret);

	if (*ret_status == TXN_IGNORE)
		return (0);

	elp->u.t.status = status;

	if (lsn != NULL && IS_ZERO_LSN(hp->maxlsn) && status == TXN_COMMIT)
		hp->maxlsn = *lsn;

	return (ret);
}
