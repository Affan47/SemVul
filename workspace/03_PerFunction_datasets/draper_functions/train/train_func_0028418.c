isns_db_create(isns_db_backend_t *backend)
{
	isns_db_t *db;

	db = isns_calloc(1, sizeof(*db));
	db->id_last_index = 1;
	db->id_last_eid = 1;
	db->id_backend = backend;
	db->id_global_scope = isns_scope_alloc(db);
	db->id_relations = isns_relation_soup_alloc();
	db->id_objects = &db->__id_objects;

	if (backend && backend->idb_reload) {
		int	status;

		status = backend->idb_reload(db);


		if (status != ISNS_SUCCESS
		 && status != ISNS_NO_SUCH_ENTRY) {
			isns_error("Error loading database: %s\n",
					isns_strerror(status));

			return NULL;
		}

		isns_db_sanity_check(db);
	}

	return db;
}
