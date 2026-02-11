chdir( pfs_name *name, char *newname ) {
		int result=-1;
		struct pfs_stat info;
		if(this->stat(name,&info)>=0) {
			if(S_ISDIR(info.st_mode)) {
				sprintf(newname,"/%s/%s:%d%s",name->service_name,name->host,name->port,name->rest);
				result = 0;
			} else {
				errno = ENOTDIR;
				result = -1;
			}
		}
		return result;
	}
