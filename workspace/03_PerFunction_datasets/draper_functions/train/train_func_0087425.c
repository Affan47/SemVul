get_mode(const bdaddr_t *bdaddr, const char *mode)
{
	if (strcasecmp("off", mode) == 0)
		return MODE_OFF;
	else if (strcasecmp("connectable", mode) == 0)
		return MODE_CONNECTABLE;
	else if (strcasecmp("discoverable", mode) == 0)
		return MODE_DISCOVERABLE;
	else if (strcasecmp("on", mode) == 0) {
		char onmode[14], srcaddr[18];

		ba2str(bdaddr, srcaddr);
		if (read_on_mode(srcaddr, onmode, sizeof(onmode)) < 0)
			return MODE_CONNECTABLE;

		return get_mode(bdaddr, onmode);
	} else
		return MODE_UNKNOWN;
}
