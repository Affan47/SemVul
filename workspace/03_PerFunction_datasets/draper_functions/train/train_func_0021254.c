chdir( pfs_name *name, char *newname ) {
		int result = -1;
		struct pfs_stat buf;
		hdfsFS fs = (hdfsFS)pfs_service_connect_cache(name);

		HDFS_CHECK_INIT(-1)
		HDFS_CHECK_FS(-1)

		debug(D_HDFS, "chdir %s", name->rest);
		if (this->_stat(fs, name, &buf) >= 0) {
			if (S_ISDIR(buf.st_mode)) {
				sprintf(newname, "/%s/%s:%d%s", name->service_name, name->host, name->port, name->rest);
				result = 0;
			} else {
				errno = ENOTDIR;
				result = -1;
			}
		}

		pfs_service_disconnect_cache(name, (void*)fs, (errno == HDFS_EINTERNAL));
		HDFS_END
	}
