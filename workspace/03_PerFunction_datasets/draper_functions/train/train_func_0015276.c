__lv_txnrgns_lsn_cmp (db, d1, d2, locp)
	DB *db;
	const DBT *d1, *d2;
	size_t *locp;
{
	struct __lv_txnrange r1, r2;

	COMPQUIET(locp, NULL);

	DB_ASSERT(db->env, d1->size == sizeof(r1));
	DB_ASSERT(db->env, d2->size == sizeof(r2));
	memcpy(&r1, d1->data, d1->size);
	memcpy(&r2, d2->data, d2->size);

	return (LOG_COMPARE(&(r1.end), &(r2.end)));
}
