read( void *data, pfs_size_t length, pfs_off_t offset ) {
		pfs_ssize_t result;

		debug(D_HDFS, "reading from file %s", name.rest);
		result = hdfs->pread(fs, handle, offset, data, length);
		HDFS_END
	}
