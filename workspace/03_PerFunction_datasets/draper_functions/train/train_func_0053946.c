odbc_txn_free(void *vdata)
{
	struct odbc_txn_frame *tx;
	AST_LIST_HEAD(, odbc_txn_frame) *oldlist = vdata;

	ast_debug(2, "odbc_txn_free(%p) called\n", vdata);

	AST_LIST_LOCK(oldlist);
	while ((tx = AST_LIST_REMOVE_HEAD(oldlist, list))) {
		release_transaction(tx);
	}
	AST_LIST_UNLOCK(oldlist);
	AST_LIST_HEAD_DESTROY(oldlist);
	ast_free(oldlist);
}
