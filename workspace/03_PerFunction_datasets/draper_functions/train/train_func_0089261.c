ext_chunkdb_ctor(int mode, const char *spec)
{
	struct chunk_db *cdb;

	if (strncmp(spec, "cmd:", 4))
		return NULL;

	TRACE("mode=%d spec=%s\n", mode, spec);

	if (mode != CHUNKDB_RO)
		return ERR_PTR(EINVAL);
	if (access(spec + 4, X_OK))
		return ERR_PTR(EACCES);

	cdb = malloc(sizeof(struct chunk_db) + strlen(spec + 4) + 1);
	if (!cdb)
		return ERR_PTR(ENOMEM);

	cdb->db_info = (void *)(cdb + 1);
	strcpy(cdb->db_info, spec + 4);

	cdb->read_chunk = fetch_chunk;
	cdb->write_chunk = NULL;

	return cdb;
}
