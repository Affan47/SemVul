tdb_delete_hash(struct tdb_context *tdb, TDB_DATA key, uint32_t hash)
{
	tdb_off_t rec_ptr;
	struct tdb_record rec;
	int ret;

	if (tdb->max_dead_records != 0) {


		if (tdb_lock(tdb, BUCKET(hash), F_WRLCK) == -1)
			return -1;

		if (tdb_count_dead(tdb, hash) >= tdb->max_dead_records) {


			tdb_purge_dead(tdb, hash);
		}

		if (!(rec_ptr = tdb_find(tdb, key, hash, &rec))) {
			tdb_unlock(tdb, BUCKET(hash), F_WRLCK);
			return -1;
		}


		rec.magic = TDB_DEAD_MAGIC;
		ret = tdb_rec_write(tdb, rec_ptr, &rec);
	}
	else {
		if (!(rec_ptr = tdb_find_lock_hash(tdb, key, hash, F_WRLCK,
						   &rec)))
			return -1;

		ret = tdb_do_delete(tdb, rec_ptr, &rec);
	}

	if (ret == 0) {
		tdb_increment_seqnum(tdb);
	}

	if (tdb_unlock(tdb, BUCKET(rec.full_hash), F_WRLCK) != 0)
		TDB_LOG((tdb, TDB_DEBUG_WARNING, "tdb_delete: WARNING tdb_unlock failed!\n"));
	return ret;
}
