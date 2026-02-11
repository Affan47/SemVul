alloc_ip(struct ppp_t *ppp)
{
	ppp->ses.ipv6 = ipdb_get_ipv6(&ppp->ses);
	if (!ppp->ses.ipv6) {
		if (gen_ipv6_item(&ppp->ses) < 0) {
			log_ppp_warn("ppp: no free IPv6 address\n");
			return IPV6CP_OPT_CLOSE;
		}
	}

	if (!ppp->ses.ipv6->intf_id)
		ppp->ses.ipv6->intf_id = generate_intf_id(ppp);

	if (conf_check_exists && check_exists(ppp))
		return IPV6CP_OPT_FAIL;

	return 0;
}
