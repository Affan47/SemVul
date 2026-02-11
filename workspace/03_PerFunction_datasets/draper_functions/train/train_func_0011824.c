tdb_traverse(struct tdb_context *tdb,
		 tdb_traverse_func fn, void *private_data)
{
	struct tdb_traverse_lock tl = { NULL, 0, 0, F_WRLCK };
	int ret;

	if (tdb->read_only || tdb->traverse_read) {
		return tdb_traverse_read(tdb, fn, private_data);
	}

	if (tdb_transaction_lock(tdb, F_WRLCK)) {
		return -1;
	}

	tdb->traverse_write++;
	tdb_trace(tdb, "tdb_traverse_start");
	ret = tdb_traverse_internal(tdb, fn, private_data, &tl);
	tdb->traverse_write--;

	tdb_transaction_unlock(tdb, F_WRLCK);

	return ret;
}
