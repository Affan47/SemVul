fcoe_if_to_netdev(const char *buffer)
{
	char *cp;
	char ifname[IFNAMSIZ + 2];

	if (buffer) {
		strlcpy(ifname, buffer, IFNAMSIZ);
		cp = ifname + strlen(ifname);
		while (--cp >= ifname && *cp == '\n')
			*cp = '\0';
		return dev_get_by_name(&init_net, ifname);
	}
	return NULL;
}
