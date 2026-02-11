nw_rpc100s_hostlist(StonithPlugin  *s)
{
	char **		ret = NULL;
	struct pluginDevice*	ctx;

	if (Debug) {
		LOG(PIL_DEBUG, "Calling nw_rpc100s_hostlist (%s)", pluginid);
	}

	ERRIFNOTCONFIGED(s,NULL);

	ctx = (struct pluginDevice*) s;

	ret = OurImports->StringToHostList(ctx->node);
	if (ret == NULL) {
		LOG(PIL_CRIT, "%s: out of memory", __FUNCTION__);
	} else {
		g_strdown(ret[0]);
	}

	return(ret);
}
