rps10_status(StonithPlugin  *s)
{
	struct pluginDevice*	ctx;

	if (Debug) {
		LOG(PIL_DEBUG, "%s:called.", __FUNCTION__);
	}

	ERRIFNOTCONFIGED(s,S_OOPS);

	ctx = (struct pluginDevice*) s;
	if (RPSConnect(ctx) != S_OK) {
		return(S_OOPS);
	}


	return(RPSDisconnect(ctx));
}
