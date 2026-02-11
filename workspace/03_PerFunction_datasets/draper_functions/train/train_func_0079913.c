repack_traverse(struct tdb_context *tdb, TDB_DATA key, TDB_DATA data,
			   struct traverse_state *state)
{
	state->error = tdb_store(state->dest_db, key, data, TDB_INSERT);
	if (state->error != TDB_SUCCESS) {
		return -1;
	}
	return 0;
}
