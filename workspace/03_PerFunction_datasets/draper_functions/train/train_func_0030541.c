server_table_load(time_t stoptime)
{
	struct catalog_query *q;
	struct nvpair *n;
	char *key;
	void *item;

	if((last_update + update_interval) > time(0)) {
		return 1;
	}

	if(!server_table) {
		server_table = hash_table_create(0, 0);
		if(!server_table)
			return 0;
	}

	if(inhibit_catalog_queries) {
		debug(D_CHIRP, "catalog queries disabled\n");
		return 1;
	}

	hash_table_firstkey(server_table);
	while(hash_table_nextkey(server_table, &key, &item)) {
		hash_table_remove(server_table, key);
		nvpair_delete(item);
	}

	debug(D_CHIRP, "querying catalog at %s:%d", CATALOG_HOST, CATALOG_PORT);

	q = catalog_query_create(CATALOG_HOST, CATALOG_PORT, stoptime);
	if(!q)
		return 0;

	while((n = catalog_query_read(q, stoptime))) {
		char name[CHIRP_PATH_MAX];
		const char *type, *hname;
		int port;

		type = nvpair_lookup_string(n, "type");
		if(type && !strcmp(type, "chirp")) {
			hname = nvpair_lookup_string(n, "name");
			if(hname) {
				port = nvpair_lookup_integer(n, "port");
				if(!port)
					port = CHIRP_PORT;
				sprintf(name, "%s:%d", hname, port);
				hash_table_insert(server_table, name, n);
			} else {
				nvpair_delete(n);
			}
		} else {
			nvpair_delete(n);
		}
	}
	catalog_query_delete(q);
	last_update = time(0);

	return 1;
}
