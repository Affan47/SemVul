remove_from_freelist(struct tdb_context *tdb, tdb_off_t off, tdb_off_t next)
{
	tdb_off_t last_ptr, i;


	last_ptr = FREELIST_TOP;
	while (tdb_ofs_read(tdb, last_ptr, &i) != -1 && i != 0) {
		if (i == off) {

			return tdb_ofs_write(tdb, last_ptr, &next);
		}

		last_ptr = i;
	}
	TDB_LOG((tdb, TDB_DEBUG_FATAL,"remove_from_freelist: not on list at off=%d\n", off));
	return TDB_ERRCODE(TDB_ERR_CORRUPT, -1);
}
