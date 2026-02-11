tdb_delete(struct tdb_context *tdb, struct tdb_data key)
{
	tdb_off_t off;
	struct tdb_used_record rec;
	struct hash_info h;
	enum TDB_ERROR ecode;

	if (tdb->flags & TDB_VERSION1) {
		if (tdb1_delete(tdb, key) == -1)
			return tdb->last_error;
		return TDB_SUCCESS;
	}

	off = find_and_lock(tdb, key, F_WRLCK, &h, &rec, NULL);
	if (TDB_OFF_IS_ERR(off)) {
		return tdb->last_error = TDB_OFF_TO_ERR(off);
	}

	if (!off) {
		ecode = TDB_ERR_NOEXIST;
		goto unlock;
	}

	ecode = delete_from_hash(tdb, &h);
	if (ecode != TDB_SUCCESS) {
		goto unlock;
	}


	tdb->stats.frees++;
	ecode = add_free_record(tdb, off,
				sizeof(struct tdb_used_record)
				+ rec_key_length(&rec)
				+ rec_data_length(&rec)
				+ rec_extra_padding(&rec),
				TDB_LOCK_WAIT, true);

	if (tdb->flags & TDB_SEQNUM)
		tdb_inc_seqnum(tdb);

unlock:
	tdb_unlock_hashes(tdb, h.hlock_start, h.hlock_range, F_WRLCK);
	return tdb->last_error = ecode;
}
