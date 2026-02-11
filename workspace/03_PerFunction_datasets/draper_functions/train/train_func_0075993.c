srv_parse_ssl(char **args, int *cur_arg, struct proxy *px, struct server *newsrv, char **err)
{
	newsrv->use_ssl = 1;
	if (global.connect_default_ciphers && !newsrv->ssl_ctx.ciphers)
		newsrv->ssl_ctx.ciphers = strdup(global.connect_default_ciphers);
	return 0;
}
