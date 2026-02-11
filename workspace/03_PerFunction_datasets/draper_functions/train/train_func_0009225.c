_stat( hdfsFS fs, pfs_name *name, struct pfs_stat *buf ) {
		int result;
		hdfsFileInfo *file_info = 0;

		if (hdfs_dircache.lookup(name->rest, buf)) {
			result = 0;
		} else {
			file_info = hdfs->stat(fs, name->rest);

			if (file_info != NULL) {
				hdfs_copy_fileinfo(name, file_info, buf);
				hdfs->free_stat(file_info, 1);
				result = 0;
			} else {
				errno = ENOENT;
				result = -1;
			}
		}

		HDFS_END
	}
