maildir_store_uid( maildir_store_t *ctx )
{
	int n;
	char buf[128];

	n = sprintf( buf, "%d\n%d\n", ctx->gen.uidvalidity, ctx->nuid );
	lseek( ctx->uvfd, 0, SEEK_SET );
	if (write( ctx->uvfd, buf, n ) != n || ftruncate( ctx->uvfd, n )) {
		error( "Maildir error: cannot write UIDVALIDITY.\n" );
		return DRV_BOX_BAD;
	}
	return DRV_OK;
}
