tdb_allrecord_unlock(struct tdb_context *tdb, int ltype, bool mark_lock)
{

	if (tdb->read_only || tdb->traverse_read) {
		tdb->ecode = TDB_ERR_LOCK;
		return -1;
	}

	if (tdb->allrecord_lock.count == 0) {
		tdb->ecode = TDB_ERR_LOCK;
		return -1;
	}


	if (tdb->allrecord_lock.ltype != ltype
	    && (!tdb->allrecord_lock.off || ltype != F_RDLCK)) {
		tdb->ecode = TDB_ERR_LOCK;
		return -1;
	}

	if (tdb->allrecord_lock.count > 1) {
		tdb->allrecord_lock.count--;
		return 0;
	}

	if (!mark_lock && tdb_brunlock(tdb, ltype, FREELIST_TOP, 0)) {
		TDB_LOG((tdb, TDB_DEBUG_ERROR, "tdb_unlockall failed (%s)\n", strerror(errno)));
		return -1;
	}

	tdb->allrecord_lock.count = 0;
	tdb->allrecord_lock.ltype = 0;

	return 0;
}
