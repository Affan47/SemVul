tdb1_wipe_all(struct tdb_context *tdb)
{
	int i;
	tdb1_off_t offset = 0;
	ssize_t data_len;
	tdb1_off_t recovery_head;
	tdb1_len_t recovery_size = 0;

	if (tdb_lockall(tdb) != TDB_SUCCESS) {
		return -1;
	}


	if (tdb1_ofs_read(tdb, TDB1_RECOVERY_HEAD, &recovery_head) == -1) {
		tdb_logerr(tdb, tdb->last_error, TDB_LOG_ERROR,
			   "tdb1_wipe_all: failed to read recovery head");
		goto failed;
	}

	if (recovery_head != 0) {
		struct tdb1_record rec;
		if (tdb->tdb1.io->tdb1_read(tdb, recovery_head, &rec, sizeof(rec), TDB1_DOCONV()) == -1) {
			tdb_logerr(tdb, tdb->last_error, TDB_LOG_ERROR,
				   "tdb1_wipe_all: failed to read recovery record");
			return -1;
		}
		recovery_size = rec.rec_len + sizeof(rec);
	}


	for (i=0;i<tdb->tdb1.header.hash_size;i++) {
		if (tdb1_ofs_write(tdb, TDB1_HASH_TOP(i), &offset) == -1) {
			tdb_logerr(tdb, tdb->last_error, TDB_LOG_ERROR,
				   "tdb1_wipe_all: failed to write hash %d", i);
			goto failed;
		}
	}


	if (tdb1_ofs_write(tdb, TDB1_FREELIST_TOP, &offset) == -1) {
		tdb_logerr(tdb, tdb->last_error, TDB_LOG_ERROR,
			   "tdb1_wipe_all: failed to write freelist");
		goto failed;
	}


	if (recovery_size == 0) {

		data_len = (tdb->file->map_size - TDB1_DATA_START(tdb->tdb1.header.hash_size));
		if (tdb1_free_region(tdb, TDB1_DATA_START(tdb->tdb1.header.hash_size), data_len) != 0) {
			goto failed;
		}
	} else {


		data_len = (recovery_head - TDB1_DATA_START(tdb->tdb1.header.hash_size));
		if (tdb1_free_region(tdb, TDB1_DATA_START(tdb->tdb1.header.hash_size), data_len) != 0) {
			goto failed;
		}

		data_len = tdb->file->map_size - (recovery_head+recovery_size);
		if (tdb1_free_region(tdb, recovery_head+recovery_size, data_len) != 0) {
			goto failed;
		}
	}

	tdb1_increment_seqnum_nonblock(tdb);
	tdb_unlockall(tdb);
	return 0;

failed:
	tdb_unlockall(tdb);
	return -1;
}
