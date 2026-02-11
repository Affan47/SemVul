put_bytes(struct tdb_context *tdb, TDB_DATA d)
{
	if (tdb->tdb1.transaction == NULL && tdb->file->map_ptr != NULL)
		return;
	free(d.dptr);
}
