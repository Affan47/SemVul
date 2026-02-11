ast_dummy_channel_destructor(void *obj)
{
	struct ast_channel *chan = obj;
	struct ast_datastore *datastore;
	struct ast_var_t *vardata;
	struct varshead *headp;

	ast_pbx_hangup_handler_destroy(chan);


	while ((datastore = AST_LIST_REMOVE_HEAD(ast_channel_datastores(chan), entry))) {

		ast_datastore_free(datastore);
	}

	ast_party_dialed_free(ast_channel_dialed(chan));
	ast_party_caller_free(ast_channel_caller(chan));
	ast_party_connected_line_free(ast_channel_connected(chan));
	ast_party_redirecting_free(ast_channel_redirecting(chan));


	headp = ast_channel_varshead(chan);
	while ((vardata = AST_LIST_REMOVE_HEAD(headp, entries)))
		ast_var_delete(vardata);

	if (ast_channel_cdr(chan)) {
		ast_cdr_discard(ast_channel_cdr(chan));
		ast_channel_cdr_set(chan, NULL);
	}

	ast_channel_internal_cleanup(chan);
}
