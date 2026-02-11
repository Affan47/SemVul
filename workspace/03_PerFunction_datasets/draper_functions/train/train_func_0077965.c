pfs_service_connect_cache( pfs_name *name )
{
	char key[PFS_PATH_MAX];
	void *cxn;

	if(!name->host[0]) {
		errno = ENOENT;
		return 0;
	}

	if(!table) table = hash_table_create(0,0);

	if(table) {
		sprintf(key,"/%s/%s:%d",name->service_name,name->host,name->port);
		cxn = hash_table_remove(table,key);
		if(cxn) return cxn;
	}

	return name->service->connect(name);
}
