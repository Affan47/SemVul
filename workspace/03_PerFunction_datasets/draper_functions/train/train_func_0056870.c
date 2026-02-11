str_to_mode(char *str)
{
	int mode;

	if (!strcmp("discovery", str))
		mode = MODE_DISCOVERY;
	else if (!strcmp("discoverydb", str))
		mode = MODE_DISCOVERYDB;
	else if (!strcmp("node", str))
		mode = MODE_NODE;
	else if (!strcmp("session", str))
		mode = MODE_SESSION;
	else if (!strcmp("iface", str))
		mode = MODE_IFACE;
	else if (!strcmp("fw", str))
		mode = MODE_FW;
	else if (!strcmp("host", str))
		mode = MODE_HOST;
	else
		mode = -1;

	return mode;
}
