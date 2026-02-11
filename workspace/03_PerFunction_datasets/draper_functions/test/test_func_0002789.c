add_plugin_host(struct krb5_krbhst_data *kd,
		const char *host,
		const char *port,
		int portnum,
		int proto)
{
    struct krb5_krbhst_info *hi;
    struct addrinfo hints, *ai;
    size_t hostlen;
    int ret;

    make_hints(&hints, proto);
    ret = getaddrinfo(host, port, &hints, &ai);
    if (ret)
	return 0;

    hostlen = strlen(host);

    hi = calloc(1, sizeof(*hi) + hostlen);
    if(hi == NULL)
	return ENOMEM;

    hi->proto = proto;
    hi->port  = hi->def_port = portnum;
    hi->ai    = ai;
    memmove(hi->hostname, host, hostlen);
    hi->hostname[hostlen] = '\0';
    append_host_hostinfo(kd, hi);

    return 0;
}
