tdb_new_database(TDB_CONTEXT *tdb, int hash_size)
{
	struct tdb_header *newdb;
	int size, ret = -1;


	size = sizeof(struct tdb_header) + (hash_size+1)*sizeof(tdb_off);
	if (!(newdb = calloc(size, 1)))
		return TDB_ERRCODE(TDB_ERR_OOM, -1);


	newdb->version = TDB_VERSION;
	newdb->hash_size = hash_size;
	if (tdb->flags & TDB_INTERNAL) {
		tdb->map_size = size;
		tdb->map_ptr = (char *)newdb;
		memcpy(&tdb->header, newdb, sizeof(tdb->header));

		CONVERT(*newdb);
		return 0;
	}
	if (lseek(tdb->fd, 0, SEEK_SET) == -1)
		goto fail;

	if (ftruncate(tdb->fd, 0) == -1)
		goto fail;


	CONVERT(*newdb);
	memcpy(&tdb->header, newdb, sizeof(tdb->header));

	memcpy(newdb->magic_food, TDB_MAGIC_FOOD, strlen(TDB_MAGIC_FOOD)+1);
	if (write(tdb->fd, newdb, size) != size)
		ret = -1;
	else
		ret = tdb_create_rwlocks(tdb->fd, hash_size);

  fail:
	SAFE_FREE(newdb);
	return ret;
}
