insert_entry(const xt_chainlabel chain,
	     struct ip6t_entry *fw,
	     unsigned int rulenum,
	     unsigned int nsaddrs,
	     const struct in6_addr saddrs[],
	     const struct in6_addr smasks[],
	     unsigned int ndaddrs,
	     const struct in6_addr daddrs[],
	     const struct in6_addr dmasks[],
	     int verbose,
	     struct xtc_handle *handle)
{
	unsigned int i, j;
	int ret = 1;

	for (i = 0; i < nsaddrs; i++) {
		fw->ipv6.src = saddrs[i];
		fw->ipv6.smsk = smasks[i];
		for (j = 0; j < ndaddrs; j++) {
			fw->ipv6.dst = daddrs[j];
			fw->ipv6.dmsk = dmasks[j];
			if (verbose)
				print_firewall_line(fw, handle);
			ret &= ip6tc_insert_entry(chain, fw, rulenum, handle);
		}
	}

	return ret;
}
