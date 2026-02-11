tdb_transaction_commit(struct tdb_context *tdb)
{
	const struct tdb_methods *methods;
	int i;
	bool need_repack;

	if (tdb->transaction == NULL) {
		TDB_LOG((tdb, TDB_DEBUG_ERROR, "tdb_transaction_commit: no transaction\n"));
		return -1;
	}

	tdb_trace(tdb, "tdb_transaction_commit");

	if (tdb->transaction->transaction_error) {
		tdb->ecode = TDB_ERR_IO;
		tdb_transaction_cancel(tdb);
		TDB_LOG((tdb, TDB_DEBUG_ERROR, "tdb_transaction_commit: transaction error pending\n"));
		return -1;
	}


	if (tdb->transaction->nesting != 0) {
		tdb->transaction->nesting--;
		return 0;
	}


	if (tdb->transaction->blocks == NULL) {
		_tdb_transaction_cancel(tdb);
		return 0;
	}

	if (!tdb->transaction->prepared) {
		int ret = _tdb_transaction_prepare_commit(tdb);
		if (ret)
			return ret;
	}

	methods = tdb->transaction->io_methods;


	for (i=0;i<tdb->transaction->num_blocks;i++) {
		tdb_off_t offset;
		tdb_len_t length;

		if (tdb->transaction->blocks[i] == NULL) {
			continue;
		}

		offset = i * tdb->transaction->block_size;
		length = tdb->transaction->block_size;
		if (i == tdb->transaction->num_blocks-1) {
			length = tdb->transaction->last_block_size;
		}

		if (methods->tdb_write(tdb, offset, tdb->transaction->blocks[i], length) == -1) {
			TDB_LOG((tdb, TDB_DEBUG_FATAL, "tdb_transaction_commit: write failed during commit\n"));


			tdb->methods = methods;
			tdb_transaction_recover(tdb);

			_tdb_transaction_cancel(tdb);

			TDB_LOG((tdb, TDB_DEBUG_FATAL, "tdb_transaction_commit: write failed\n"));
			return -1;
		}
		SAFE_FREE(tdb->transaction->blocks[i]);
	}

	SAFE_FREE(tdb->transaction->blocks);
	tdb->transaction->num_blocks = 0;


	if (transaction_sync(tdb, 0, tdb->map_size) == -1) {
		return -1;
	}


#if HAVE_UTIME
	utime(tdb->name, NULL);
#endif

	need_repack = tdb->transaction->need_repack;


	_tdb_transaction_cancel(tdb);

	if (need_repack) {
		return tdb_repack(tdb);
	}

	return 0;
}
