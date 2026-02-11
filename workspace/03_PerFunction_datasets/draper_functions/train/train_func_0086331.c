insert_entry(const xt_chainlabel chain,
	     struct ipt_entry *fw,
	     unsigned int rulenum,
	     unsigned int nsaddrs,
	     const struct in_addr saddrs[],
	     const struct in_addr smasks[],
	     unsigned int ndaddrs,
	     const struct in_addr daddrs[],
	     const struct in_addr dmasks[],
	     int verbose,
	     struct xtc_handle *handle)
{
	unsigned int i, j;
	int ret = 1;

	for (i = 0; i < nsaddrs; i++) {
		fw->ip.src.s_addr = saddrs[i].s_addr;
		fw->ip.smsk.s_addr = smasks[i].s_addr;
		for (j = 0; j < ndaddrs; j++) {
			fw->ip.dst.s_addr = daddrs[j].s_addr;
			fw->ip.dmsk.s_addr = dmasks[j].s_addr;
			if (verbose)
				print_firewall_line(fw, handle);
			ret &= iptc_insert_entry(chain, fw, rulenum, handle);
		}
	}

	return ret;
}
