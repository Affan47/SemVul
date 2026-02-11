handle_reg_set(struct nl80211_state *state,
			  struct nl_cb *cb,
			  struct nl_msg *msg,
			  int argc, char **argv)
{
	char alpha2[3];

	if (argc < 1)
		return 1;

	if (!is_alpha2(argv[0]) && !is_world_regdom(argv[0])) {
		fprintf(stderr, "not a valid ISO/IEC 3166-1 alpha2\n");
		fprintf(stderr, "Special non-alpha2 usable entries:\n");
		fprintf(stderr, "\t00\tWorld Regulatory domain\n");
		return 2;
	}

	alpha2[0] = argv[0][0];
	alpha2[1] = argv[0][1];
	alpha2[2] = '\0';

	argc--;
	argv++;

	if (argc)
		return 1;

	NLA_PUT_STRING(msg, NL80211_ATTR_REG_ALPHA2, alpha2);

	return 0;
 nla_put_failure:
	return -ENOBUFS;
}
