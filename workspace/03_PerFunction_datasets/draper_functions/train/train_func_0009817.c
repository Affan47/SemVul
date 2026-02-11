tdb_rec_read(struct tdb_context *tdb, tdb_off_t offset, struct tdb_record *rec)
{
	if (tdb->methods->tdb_read(tdb, offset, rec, sizeof(*rec),DOCONV()) == -1)
		return -1;
	if (TDB_BAD_MAGIC(rec)) {

		tdb->ecode = TDB_ERR_CORRUPT;
		TDB_LOG((tdb, TDB_DEBUG_FATAL,"tdb_rec_read bad magic 0x%x at offset=%d\n", rec->magic, offset));
		return -1;
	}
	return tdb->methods->tdb_oob(tdb, rec->next+sizeof(*rec), 0);
}
