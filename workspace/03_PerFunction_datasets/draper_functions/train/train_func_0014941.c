tdb1_next_lock(struct tdb_context *tdb, struct tdb1_traverse_lock *tlock,
			 struct tdb1_record *rec)
{
	int want_next = (tlock->off != 0);


	for (; tlock->hash < tdb->tdb1.header.hash_size; tlock->hash++) {
		if (!tlock->off && tlock->hash != 0) {


			tdb->tdb1.io->next_hash_chain(tdb, &tlock->hash);
			if (tlock->hash == tdb->tdb1.header.hash_size) {
				continue;
			}
		}

		if (tdb1_lock(tdb, tlock->hash, tlock->lock_rw) == -1)
			return TDB1_NEXT_LOCK_ERR;


		if (!tlock->off) {
			if (tdb1_ofs_read(tdb, TDB1_HASH_TOP(tlock->hash),
				     &tlock->off) == -1)
				goto fail;
		} else {

			if (tdb1_unlock_record(tdb, tlock->off) != 0)
				goto fail;
		}

		if (want_next) {

			if (tdb1_rec_read(tdb, tlock->off, rec) == -1)
				goto fail;
			tlock->off = rec->next;
		}


		while( tlock->off) {
			tdb1_off_t current;
			if (tdb1_rec_read(tdb, tlock->off, rec) == -1)
				goto fail;


			if (tlock->off == rec->next) {
				tdb->last_error = tdb_logerr(tdb, TDB_ERR_CORRUPT,
							TDB_LOG_ERROR,
							"tdb1_next_lock:"
							" loop detected.");
				goto fail;
			}

			if (!TDB1_DEAD(rec)) {

				if (tdb1_lock_record(tdb, tlock->off) != 0)
					goto fail;
				return tlock->off;
			}


			current = tlock->off;
			tlock->off = rec->next;
			if (!((tdb->flags & TDB_RDONLY) || tdb->tdb1.traverse_read) &&
			    tdb1_do_delete(tdb, current, rec) != 0)
				goto fail;
		}
		tdb1_unlock(tdb, tlock->hash, tlock->lock_rw);
		want_next = 0;
	}

	tdb->last_error = TDB_SUCCESS;
	return 0;

 fail:
	tlock->off = 0;
	if (tdb1_unlock(tdb, tlock->hash, tlock->lock_rw) != 0)
		tdb_logerr(tdb, tdb->last_error, TDB_LOG_ERROR,
			   "tdb1_next_lock: On error unlock failed!");
	return TDB1_NEXT_LOCK_ERR;
}
