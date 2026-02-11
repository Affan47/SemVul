maildir_open_store( store_conf_t *conf, const char *label ATTR_UNUSED,
                    void (*cb)( store_t *ctx, void *aux ), void *aux )
{
	maildir_store_t *ctx;
	struct stat st;

	if (stat( conf->path, &st ) || !S_ISDIR(st.st_mode)) {
		error( "Maildir error: cannot open store '%s'\n", conf->path );
		cb( 0, aux );
		return;
	}
	ctx = nfcalloc( sizeof(*ctx) );
	ctx->gen.conf = conf;
	ctx->uvfd = -1;
	if (conf->trash)
		ctx->trash = maildir_join_path( conf->path, conf->trash );
	cb( &ctx->gen, aux );
}
