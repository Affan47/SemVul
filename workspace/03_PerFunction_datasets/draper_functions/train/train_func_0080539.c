__del_txn_pages(lvinfo, txnid)
	DB_LOG_VRFY_INFO *lvinfo;
	u_int32_t txnid;
{
	int ret;
	DBT key;

	ret = 0;
	memset(&key, 0, sizeof(DBT));
	key.data = &txnid;
	key.size = sizeof(txnid);

	BDBOP(__db_del(lvinfo->txnpg, lvinfo->ip, NULL, &key, 0));

err:
	return (ret);
}
