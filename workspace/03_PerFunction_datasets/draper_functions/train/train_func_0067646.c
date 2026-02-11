iface_match_default(struct iface_rec *iface)
{
	struct iface_rec *def_iface;
	int i = 0;

	while ((def_iface = default_ifaces[i++])) {
		if (!strcmp(iface->name, def_iface->name))
			return def_iface;
	}
	return NULL;
}
