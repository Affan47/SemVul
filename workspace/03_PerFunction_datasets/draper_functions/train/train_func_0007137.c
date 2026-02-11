tdb_brlock(struct tdb_context *tdb,
			  int rw_type, tdb_off_t offset, tdb_off_t len,
			  enum tdb_lock_flags flags)
{
	int ret;

	if (tdb->flags & TDB_NOLOCK) {
		return TDB_SUCCESS;
	}

	if (rw_type == F_WRLCK && (tdb->flags & TDB_RDONLY)) {
		return tdb_logerr(tdb, TDB_ERR_RDONLY, TDB_LOG_USE_ERROR,
				  "Write lock attempted on read-only database");
	}


	if ((size_t)(offset + len) != offset + len) {
		return tdb_logerr(tdb, TDB_ERR_IO, TDB_LOG_ERROR,
				  "tdb_brlock: lock on giant offset %llu",
				  (long long)(offset + len));
	}

	ret = lock(tdb, rw_type, offset, len, flags & TDB_LOCK_WAIT);
	if (ret != 0) {


		if (!(flags & TDB_LOCK_PROBE)
		    && (errno != EAGAIN && errno != EINTR)) {
			tdb_logerr(tdb, TDB_ERR_LOCK, TDB_LOG_ERROR,
				   "tdb_brlock failed (fd=%d) at"
				   " offset %zu rw_type=%d flags=%d len=%zu:"
				   " %s",
				   tdb->file->fd, (size_t)offset, rw_type,
				   flags, (size_t)len, strerror(errno));
		}
		return TDB_ERR_LOCK;
	}
	return TDB_SUCCESS;
}
