webdav_copy_file(server *srv, connection *con, plugin_data *p, physical *src, physical *dst, int overwrite) {
	stream s;
	int status = 0, ofd;
	UNUSED(srv);
	UNUSED(con);

	if (stream_open(&s, src->path)) {
		return 403;
	}

	if (-1 == (ofd = open(dst->path->ptr, O_WRONLY|O_TRUNC|O_CREAT|(overwrite ? 0 : O_EXCL), WEBDAV_FILE_MODE))) {

		switch(errno) {
		case EEXIST:
			status = 412;
			break;
		case EISDIR:
			status = 409;
			break;
		case ENOENT:

			status = 409;
			break;
		default:
			status = 403;
			break;
		}
		stream_close(&s);
		return status;
	}

	if (-1 == write(ofd, s.start, s.size)) {
		switch(errno) {
		case ENOSPC:
			status = 507;
			break;
		default:
			status = 403;
			break;
		}
	}

	stream_close(&s);
	close(ofd);

#ifdef USE_PROPPATCH
	if (0 == status) {

		sqlite3_stmt *stmt = p->conf.stmt_copy_uri;

		if (stmt) {
			sqlite3_reset(stmt);


			sqlite3_bind_text(stmt, 1,
					  dst->rel_path->ptr,
					  dst->rel_path->used - 1,
					  SQLITE_TRANSIENT);

			sqlite3_bind_text(stmt, 2,
					  src->rel_path->ptr,
					  src->rel_path->used - 1,
					  SQLITE_TRANSIENT);

			if (SQLITE_DONE != sqlite3_step(stmt)) {

			}
		}
	}
#else
	UNUSED(p);
#endif
	return status;
}
