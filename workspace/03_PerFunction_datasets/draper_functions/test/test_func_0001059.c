check_free(struct tdb_context *tdb,
				 tdb_off_t off,
				 const struct tdb_free_record *frec,
				 tdb_off_t prev, unsigned int ftable,
				 unsigned int bucket)
{
	enum TDB_ERROR ecode;

	if (frec_magic(frec) != TDB_FREE_MAGIC) {
		return tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_ERROR,
				  "tdb_check: offset %llu bad magic 0x%llx",
				  (long long)off,
				  (long long)frec->magic_and_prev);
	}
	if (frec_ftable(frec) != ftable) {
		return tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_ERROR,
				  "tdb_check: offset %llu bad freetable %u",
				  (long long)off, frec_ftable(frec));

	}

	ecode = tdb->tdb2.io->oob(tdb, off
				  + frec_len(frec)
				  + sizeof(struct tdb_used_record),
				  false);
	if (ecode != TDB_SUCCESS) {
		return ecode;
	}
	if (size_to_bucket(frec_len(frec)) != bucket) {
		return tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_ERROR,
				  "tdb_check: offset %llu in wrong bucket"
				  " (%u vs %u)",
				  (long long)off,
				  bucket, size_to_bucket(frec_len(frec)));
	}
	if (prev && prev != frec_prev(frec)) {
		return tdb_logerr(tdb, TDB_ERR_CORRUPT, TDB_LOG_ERROR,
				  "tdb_check: offset %llu bad prev"
				  " (%llu vs %llu)",
				  (long long)off,
				  (long long)prev, (long long)frec_len(frec));
	}
	return TDB_SUCCESS;
}
