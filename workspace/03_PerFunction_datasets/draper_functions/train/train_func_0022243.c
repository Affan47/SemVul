db_destructor(void *obj)
{
	struct realtime_sqlite3_db *db = obj;

	ast_debug(1, "Destroying db: %s\n", db->name);
	ast_string_field_free_memory(db);
	db_stop_batch(db);
	if (db->handle) {
		ao2_lock(db);
		sqlite3_close(db->handle);
		ao2_unlock(db);
	}
}
