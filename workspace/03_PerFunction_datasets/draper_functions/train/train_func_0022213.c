ghc_host_eof(struct parse_context *ctx)
{
	char msg[256];

	if (GNET_PROPERTY(bootstrap_debug) > 2)
		g_debug("BOOT GHC all done (%u/%u lines processed)",
			ctx->processed, ctx->lines);


	str_bprintf(msg, sizeof(msg),
		NG_("Got %d host from %s", "Got %d hosts from %s", ctx->processed),
		ctx->processed, http_async_info(ghc_ctx.ha, NULL, NULL, NULL, NULL));

	gcu_statusbar_message(msg);

	if (GNET_PROPERTY(bootstrap_debug))
		g_debug("BOOT GHC got %d host%s from %s",
			ctx->processed, ctx->processed == 1 ? "" : "s",
			http_async_info(ghc_ctx.ha, NULL, NULL, NULL, NULL));

	ghc_ctx.ha = NULL;
	ghc_connecting = FALSE;
}
