parse_list_rsp( imap_store_t *ctx, list_t *list, char *cmd )
{
	char *arg;
	list_t *lp;

	if (!is_list( list )) {
		error( "IMAP error: malformed LIST response\n" );
		free_list( list );
		return LIST_BAD;
	}
	for (lp = list->child; lp; lp = lp->next)
		if (is_atom( lp ) && !strcasecmp( lp->val, "\\NoSelect" )) {
			free_list( list );
			return LIST_OK;
		}
	free_list( list );
	arg = next_arg( &cmd );
	if (!ctx->delimiter)
		ctx->delimiter = nfstrdup( arg );
	return parse_list( ctx, cmd, parse_list_rsp_p2 );
}
