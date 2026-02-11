initialize() {
		int result;

		debug(D_HDFS, "loading dynamically shared libraries");
		hdfs = hdfs_library_open();
		if(!hdfs){
			is_initialized = false;
			result = -1;
		} else {
			is_initialized = true;
			result = 0;
		}

		HDFS_END
	}
