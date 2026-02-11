tdb_get_seqnum(struct tdb_context *tdb)
{
	tdb_off_t off;

	if (tdb->flags & TDB_VERSION1) {
		tdb1_off_t val;
		tdb->last_error = TDB_SUCCESS;
		val = tdb1_get_seqnum(tdb);

		if (tdb->last_error != TDB_SUCCESS)
			return TDB_ERR_TO_OFF(tdb->last_error);
		else
			return val;
	}

	off = tdb_read_off(tdb, offsetof(struct tdb_header, seqnum));
	if (TDB_OFF_IS_ERR(off))
		tdb->last_error = TDB_OFF_TO_ERR(off);
	else
		tdb->last_error = TDB_SUCCESS;
	return off;
}
