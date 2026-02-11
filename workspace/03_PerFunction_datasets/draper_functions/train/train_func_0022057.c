__db_txnlist_find(env, hp, txnid, statusp)
	ENV *env;
	DB_TXNHEAD *hp;
	u_int32_t txnid, *statusp;
{
	DB_TXNLIST *entry;

	if (txnid == 0)
		return (DB_NOTFOUND);

	return (__db_txnlist_find_internal(env, hp,
	    TXNLIST_TXNID, txnid, &entry, 0, statusp));
}
