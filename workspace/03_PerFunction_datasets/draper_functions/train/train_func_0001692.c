null_new(const char *subplugin)
{
	struct pluginDevice*	nd = ST_MALLOCT(struct pluginDevice);

	if (nd == NULL) {
		LOG(PIL_CRIT, "out of memory");
		return(NULL);
	}
	memset(nd, 0, sizeof(*nd));
	nd->pluginid = pluginid;
	nd->idinfo = DEVICE;
	nd->sp.s_ops = &nullOps;
	return (StonithPlugin *)nd;
}
