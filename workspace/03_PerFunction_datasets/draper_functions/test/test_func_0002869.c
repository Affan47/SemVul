rename( pfs_name *name, pfs_name *newname ) {
		INT64_T result;
		time_t stoptime = time(0) + pfs_master_timeout;

		chirp_dircache_invalidate();

		if(!strcmp(name->hostport,newname->hostport)) {
			result = chirp_global_rename(name->hostport,name->rest,newname->rest,stoptime);
		} else {
			result = chirp_global_thirdput(name->hostport,name->rest,newname->hostport,newname->rest,stoptime);
			if(result>=0) {
				result = 0;
				chirp_global_rmall(name->hostport,name->rest,stoptime);
			} else {
				errno = EXDEV;
			}
		}
		return result;

	}
