sqlite_chunkdb_ctor(int mode, const char *spec)
{
	struct chunk_db *cdb;
	struct db_info *db_info;
	int err;

	if (strncmp(spec, "sqlite:", 7))
		return NULL;

	cdb = malloc(sizeof(struct chunk_db) + sizeof(struct db_info));
	if (!cdb)
		return ERR_PTR(ENOMEM);

	db_info = cdb->db_info = (void *)(cdb + 1);
	init_mutex(&db_info->mutex);

	err = sqlite3_open(spec + 7, &db_info->db);
	if (err != SQLITE_OK) {
		fprintf(stderr, "Can't open SQLite database '%s': %s\n",
				spec + 7, sqlite3_errmsg(db_info->db));
		sqlite3_close(db_info->db);
		free(cdb);
		return ERR_PTR(EINVAL);
	}

	cdb->read_chunk = read_chunk_sqlite;
	cdb->write_chunk = (mode == CHUNKDB_RW) ? write_chunk_sqlite : NULL;

	return cdb;
}
