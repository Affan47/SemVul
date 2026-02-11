tdb_mmap(struct tdb_context *tdb)
{
	int mmap_flags;

	if (tdb->flags & TDB_INTERNAL)
		return;

	if (tdb->flags & TDB_NOMMAP)
		return;

	if ((tdb->open_flags & O_ACCMODE) == O_RDONLY)
		mmap_flags = PROT_READ;
	else
		mmap_flags = PROT_READ | PROT_WRITE;


	if ((size_t)tdb->file->map_size == tdb->file->map_size) {
		tdb->file->map_ptr = mmap(NULL, tdb->file->map_size,
					  mmap_flags,
					  MAP_SHARED, tdb->file->fd, 0);
	} else
		tdb->file->map_ptr = MAP_FAILED;


	if (tdb->file->map_ptr == MAP_FAILED) {
		tdb->file->map_ptr = NULL;
		tdb_logerr(tdb, TDB_SUCCESS, TDB_LOG_WARNING,
			   "tdb_mmap failed for size %lld (%s)",
			   (long long)tdb->file->map_size, strerror(errno));
	}
}
