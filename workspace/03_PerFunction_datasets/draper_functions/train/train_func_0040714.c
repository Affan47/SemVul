imap_cleanup( void )
{
	store_t *ctx, *nctx;

	for (ctx = unowned; ctx; ctx = nctx) {
		nctx = ctx->next;
		imap_exec( (imap_store_t *)ctx, 0, "LOGOUT" );
		imap_cancel_store( ctx );
	}
}
