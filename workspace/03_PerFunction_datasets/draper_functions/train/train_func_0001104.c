handle_mpath_set(struct nl80211_state *state,
			    struct nl_cb *cb,
			    struct nl_msg *msg,
			    int argc, char **argv)
{
	unsigned char dst[ETH_ALEN];
	unsigned char next_hop[ETH_ALEN];

	if (argc < 3)
		return 1;

	if (mac_addr_a2n(dst, argv[0])) {
		fprintf(stderr, "invalid destination mac address\n");
		return 2;
	}
	argc--;
	argv++;

	if (strcmp("next_hop", argv[0]) != 0)
		return 1;
	argc--;
	argv++;

	if (mac_addr_a2n(next_hop, argv[0])) {
		fprintf(stderr, "invalid next hop mac address\n");
		return 2;
	}
	argc--;
	argv++;

	if (argc)
		return 1;

	NLA_PUT(msg, NL80211_ATTR_MAC, ETH_ALEN, dst);
	NLA_PUT(msg, NL80211_ATTR_MPATH_NEXT_HOP, ETH_ALEN, next_hop);

	nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, print_mpath_handler, NULL);
	return 0;
 nla_put_failure:
	return -ENOBUFS;
}
