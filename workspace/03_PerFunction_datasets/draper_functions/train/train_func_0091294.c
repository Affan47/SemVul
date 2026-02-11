tdb1_write_unlock_record(struct tdb_context *tdb, tdb1_off_t off)
{
	if (tdb->file->allrecord_lock.count) {
		if (tdb->file->allrecord_lock.owner != tdb) {
			tdb->last_error
				= owner_conflict(tdb,
						 "tdb1_write_unlock_record");
			return -1;
		}
		return 0;
	}
	return tdb1_brunlock(tdb, F_WRLCK, off, 1);
}
