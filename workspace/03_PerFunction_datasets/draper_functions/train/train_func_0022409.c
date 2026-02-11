imap_open_store_tlsstarted1( int ok, void *aux )
{
	imap_store_t *ctx = (imap_store_t *)aux;

	if (!ok)
		imap_open_store_ssl_bail( ctx );
}
