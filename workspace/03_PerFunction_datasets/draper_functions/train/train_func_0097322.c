tdb_lock_and_recover(struct tdb_context *tdb)
{
	enum TDB_ERROR ecode;

	if (!check_lock_pid(tdb, "tdb_transaction_prepare_commit", true))
		return TDB_ERR_LOCK;

	ecode = tdb_allrecord_lock(tdb, F_WRLCK, TDB_LOCK_WAIT|TDB_LOCK_NOCHECK,
				   false);
	if (ecode != TDB_SUCCESS) {
		return ecode;
	}

	ecode = tdb_lock_open(tdb, F_WRLCK, TDB_LOCK_WAIT|TDB_LOCK_NOCHECK);
	if (ecode != TDB_SUCCESS) {
		tdb_allrecord_unlock(tdb, F_WRLCK);
		return ecode;
	}
	ecode = tdb_transaction_recover(tdb);
	tdb_unlock_open(tdb, F_WRLCK);
	tdb_allrecord_unlock(tdb, F_WRLCK);

	return ecode;
}
