conf_connect_allowed(struct sockaddr *addr, int aftype)
{
	struct ConfItem *aconf = find_dline(addr);


	if(aconf && (aconf->status & CONF_EXEMPTDLINE))
		return NULL;

	if(aconf != NULL)
		return aconf;

	return NULL;
}
