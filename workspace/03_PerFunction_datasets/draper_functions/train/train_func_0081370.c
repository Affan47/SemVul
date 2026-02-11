tdb1_rec_free_read(struct tdb_context *tdb, tdb1_off_t off, struct tdb1_record *rec)
{
	if (tdb->tdb1.io->tdb1_read(tdb, off, rec, sizeof(*rec),TDB1_DOCONV()) == -1)
		return -1;

	if (rec->magic == TDB1_MAGIC) {


		tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_WARNING,
			   "tdb1_rec_free_read non-free magic 0x%x at offset=%d - fixing\n",
			   rec->magic, off);
		rec->magic = TDB1_FREE_MAGIC;
		if (tdb->tdb1.io->tdb1_write(tdb, off, rec, sizeof(*rec)) == -1)
			return -1;
	}

	if (rec->magic != TDB1_FREE_MAGIC) {
		tdb->last_error = tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_ERROR,
					"tdb1_rec_free_read bad magic 0x%x at offset=%d\n",
					rec->magic, off);
		return -1;
	}
	if (tdb->tdb1.io->tdb1_oob(tdb, rec->next+sizeof(*rec), 0) != 0)
		return -1;
	return 0;
}
