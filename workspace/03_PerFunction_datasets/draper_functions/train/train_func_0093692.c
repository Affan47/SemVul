tdb_read(struct tdb_context *tdb, tdb_off_t off, void *buf,
		    tdb_len_t len, int cv)
{
	if (tdb->methods->tdb_oob(tdb, off + len, 0) != 0) {
		return -1;
	}

	if (tdb->map_ptr) {
		memcpy(buf, off + (char *)tdb->map_ptr, len);
	} else {
		ssize_t ret = pread(tdb->fd, buf, len, off);
		if (ret != (ssize_t)len) {

			tdb->ecode = TDB_ERR_IO;
			TDB_LOG((tdb, TDB_DEBUG_FATAL,"tdb_read failed at %d "
				 "len=%d ret=%d (%s) map_size=%d\n",
				 (int)off, (int)len, (int)ret, strerror(errno),
				 (int)tdb->map_size));
			return TDB_ERRCODE(TDB_ERR_IO, -1);
		}
	}
	if (cv) {
		tdb_convert(buf, len);
	}
	return 0;
}
