xtopt_parse_host(struct xt_option_call *cb)
{
	struct addrinfo hints = {.ai_family = afinfo->family};
	unsigned int adcount = 0;
	struct addrinfo *res, *p;
	int ret;

	ret = getaddrinfo(cb->arg, NULL, &hints, &res);
	if (ret < 0)
		xt_params->exit_err(PARAMETER_PROBLEM,
			"getaddrinfo: %s\n", gai_strerror(ret));

	memset(&cb->val.hmask, 0xFF, sizeof(cb->val.hmask));
	cb->val.hlen = (afinfo->family == NFPROTO_IPV4) ? 32 : 128;

	for (p = res; p != NULL; p = p->ai_next) {
		if (adcount == 0) {
			memset(&cb->val.haddr, 0, sizeof(cb->val.haddr));
			memcpy(&cb->val.haddr,
			       xtables_sa_host(p->ai_addr, p->ai_family),
			       xtables_sa_hostlen(p->ai_family));
			++adcount;
			continue;
		}
		if (memcmp(&cb->val.haddr,
		    xtables_sa_host(p->ai_addr, p->ai_family),
		    xtables_sa_hostlen(p->ai_family)) != 0)
			xt_params->exit_err(PARAMETER_PROBLEM,
				"%s resolves to more than one address\n",
				cb->arg);
	}

	freeaddrinfo(res);
	if (cb->entry->flags & XTOPT_PUT)

		memcpy(XTOPT_MKPTR(cb), &cb->val.haddr,
		       sizeof(cb->val.haddr));
}
