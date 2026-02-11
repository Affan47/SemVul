mdb_txn_abort(MDB_txn *txn)
{
	if (txn == NULL)
		return;

	DPRINTF("abort txn %zu%c %p on mdbenv %p, root page %zu",
		txn->mt_txnid, (txn->mt_flags & MDB_TXN_RDONLY) ? 'r' : 'w',
		(void *)txn, (void *)txn->mt_env, txn->mt_dbs[MAIN_DBI].md_root);

	if (txn->mt_child)
		mdb_txn_abort(txn->mt_child);

	mdb_txn_reset0(txn);
	free(txn);
}
