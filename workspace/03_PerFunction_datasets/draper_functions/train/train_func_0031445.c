find_address_conf(const char *host, const char *sockhost, const char *user,
		  struct sockaddr *ip, int aftype)
{
	struct ConfItem *iconf, *kconf;


	if(!(iconf = find_auth(host, sockhost, ip, aftype, user)))
		return NULL;


	if(IsConfExemptKline(iconf))
		return iconf;


	kconf = find_conf_by_address(host, sockhost, ip, CONF_KILL, aftype, user);


	if(kconf)
		return kconf;


	if(IsConfDoSpoofIp(iconf))
	{
		char *p = strchr(iconf->info.name, '@');


		if(p)
		{
			*p = '\0';
			kconf = find_conf_by_address(p + 1, NULL, ip, CONF_KILL, aftype,
						     iconf->info.name);
			*p = '@';
		}
		else
			kconf = find_conf_by_address(iconf->info.name, NULL, ip, CONF_KILL, aftype,
						     user);

		if(kconf)
			return kconf;
	}


	if(ConfigFileEntry.glines)
	{
		kconf = find_conf_by_address(host, sockhost, ip, CONF_GLINE, aftype, user);

		if((kconf != NULL) && !IsConfExemptGline(iconf))
			return kconf;
	}

	return iconf;
}
