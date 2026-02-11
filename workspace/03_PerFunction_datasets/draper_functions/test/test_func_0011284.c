RPSOn(struct pluginDevice* ctx, char unit_id, const char * host)
{
	if (Debug) {
		LOG(PIL_DEBUG, "%s:called.", __FUNCTION__);
	}

	if (ctx->fd < 0) {
		LOG(PIL_CRIT, "%s: device %s is not open!", pluginid,
		       ctx->device);
		return S_OOPS;
	}


	SENDCMD(unit_id, '1', 10);


	EXPECT(ctx->fd, WTItokPlug, 5);
	EXPECT(ctx->fd, WTItokOutlet, 2);
	EXPECT(ctx->fd, WTItokOn, 2);
	EXPECT(ctx->fd, WTItokCRNL, 2);
	LOG(PIL_INFO, "Host is being turned on: %s", host);


	EXPECT(ctx->fd, WTItokComplete, 5);
	EXPECT(ctx->fd, WTItokCRNL, 2);

	return(S_OK);

}
