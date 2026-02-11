webdav_delete_dir(server *srv, connection *con, plugin_data *p, physical *dst, buffer *b) {
	DIR *dir;
	int have_multi_status = 0;
	physical d;

	d.path = buffer_init();
	d.rel_path = buffer_init();

	if (NULL != (dir = opendir(dst->path->ptr))) {
		struct dirent *de;

		while(NULL != (de = readdir(dir))) {
			struct stat st;
			int status = 0;

			if ((de->d_name[0] == '.' && de->d_name[1] == '\0')  ||
			    (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')) {
				continue;

			}

			buffer_copy_string_buffer(d.path, dst->path);
			BUFFER_APPEND_SLASH(d.path);
			buffer_append_string(d.path, de->d_name);

			buffer_copy_string_buffer(d.rel_path, dst->rel_path);
			BUFFER_APPEND_SLASH(d.rel_path);
			buffer_append_string(d.rel_path, de->d_name);


			if (-1 == stat(d.path->ptr, &st)) {

			} else if (S_ISDIR(st.st_mode)) {
				have_multi_status = webdav_delete_dir(srv, con, p, &d, b);


				if (-1 == rmdir(d.path->ptr)) {
					switch(errno) {
					case EACCES:
					case EPERM:

						status = 403;
						break;
					default:
						status = 501;
						break;
					}
					have_multi_status = 1;

					webdav_gen_response_status_tag(srv, con, &d, status, b);
				} else {
#ifdef USE_PROPPATCH
					sqlite3_stmt *stmt = p->conf.stmt_delete_uri;

					status = 0;

					if (stmt) {
						sqlite3_reset(stmt);


						sqlite3_bind_text(stmt, 1,
								  d.rel_path->ptr,
								  d.rel_path->used - 1,
								  SQLITE_TRANSIENT);

						if (SQLITE_DONE != sqlite3_step(stmt)) {

						}
					}
#endif
				}
			} else {
				have_multi_status = webdav_delete_file(srv, con, p, &d, b);
			}
		}
		closedir(dir);

		buffer_free(d.path);
		buffer_free(d.rel_path);
	}

	return have_multi_status;
}
