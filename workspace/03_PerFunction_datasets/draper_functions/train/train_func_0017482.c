rps10_destroy(StonithPlugin *s)
{
	struct pluginDevice* ctx;
	int i;

	if (Debug) {
		LOG(PIL_DEBUG, "%s:called.", __FUNCTION__);
	}

	VOIDERRIFWRONGDEV(s);

	ctx = (struct pluginDevice *)s;

	ctx->pluginid = NOTwtiid;


	RPSDisconnect(ctx);

	if (ctx->device != NULL) {
		FREE(ctx->device);
		ctx->device = NULL;
	}
	if (ctx->unit_count > 0) {
		for (i = 0; i < ctx->unit_count; i++) {
			if (ctx->controllers[i].node != NULL) {
				FREE(ctx->controllers[i].node);
				ctx->controllers[i].node = NULL;
			}
		}
	}
	FREE(ctx);
}
