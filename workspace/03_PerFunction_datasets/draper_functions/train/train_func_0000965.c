get_bytes(struct tdb_context *tdb,
			  tdb1_off_t off, tdb1_len_t len)
{
	TDB_DATA d;

	d.dsize = len;

	if (tdb->tdb1.transaction == NULL && tdb->file->map_ptr != NULL)
		d.dptr = (unsigned char *)tdb->file->map_ptr + off;
	else
		d.dptr = tdb1_alloc_read(tdb, off, d.dsize);
	return d;
}
