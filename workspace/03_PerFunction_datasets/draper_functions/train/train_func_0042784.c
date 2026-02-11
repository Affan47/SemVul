connect( pfs_name *name ) {
		hdfsFS fs;
		HDFS_CHECK_INIT(0)

		debug(D_HDFS, "connecting to %s:%d", name->host, name->port);
		fs = hdfs->connect(name->host, name->port);
		if (errno == HDFS_EINTERNAL) {
			errno = ECONNRESET;
		}

		debug(D_HDFS, "= %ld", fs);
		return fs;
	}
