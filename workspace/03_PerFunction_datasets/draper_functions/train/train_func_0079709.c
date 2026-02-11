domain_name_cache_guess(char *name)
{
	struct utsname n;
	char addr[DOMAIN_NAME_MAX];
	char domain[DOMAIN_NAME_MAX];

	if(uname(&n) < 0)
		return 0;

	if(!domain_name_cache_lookup(n.nodename, addr))
		return 0;
	if(!domain_name_cache_lookup_reverse(addr, name))
		return 0;

	debug(D_DNS, "finding my hostname: uname = %s, address = %s, hostname = %s", n.nodename, addr, name);

	if(!strncmp(name, "localhost", 9) || !strcmp(addr, "127.0.0.1")) {
		debug(D_DNS, "local address of '%s' (%s) is not very useful.", name, addr);
		if(guess_dns_domain(domain)) {
			sprintf(name, "%s.%s", n.nodename, domain);
			debug(D_DNS, "but /etc/resolv.conf says domain = %s so hostname = %s", domain, name);
			if(!domain_name_cache_lookup(name, addr)) {
				debug(D_DNS, "unfortunately %s is meaningless, so going back to %s", name, n.nodename);
				sprintf(name, "%s", n.nodename);
			}
		} else {
			strcpy(name, n.nodename);
			debug(D_DNS, "cannot find any more info, so use hostname = %s", n.nodename);
		}
	}

	return 1;
}
