parse_tproxy_laddr(const char *s, union nf_inet_addr *addrp,
			       unsigned int nfproto)
{
	struct in6_addr *laddr6 = NULL;
	struct in_addr *laddr4 = NULL;

	if (nfproto == NFPROTO_IPV6) {
		laddr6 = xtables_numeric_to_ip6addr(s);
		if (laddr6 == NULL)
			goto out;
		addrp->in6 = *laddr6;
	} else if (nfproto == NFPROTO_IPV4) {
		laddr4 = xtables_numeric_to_ipaddr(s);
		if (laddr4 == NULL)
			goto out;
		addrp->in = *laddr4;
	}
	return;
 out:
	xtables_param_act(XTF_BAD_VALUE, "TPROXY", "--on-ip", s);
}
