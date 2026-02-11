db_table_get_read(char* name, int length){
	uint32_t hash = hash_string(name, length);

	khiter_t k = kh_get(table, db.tables, hash);

	if (k == kh_end(db.tables)){
		free(name);
		return NULL;
	}

	db_table* entry = kh_value(db.tables, k);

	free(name);
	assert(entry != NULL);

	db_table_incref(entry);

	return entry;
}
