__multiport_parse(int c, char **argv, int invert, unsigned int *flags,
                  struct xt_entry_match **match, uint16_t pnum,
                  uint8_t invflags)
{
	const char *proto;
	struct xt_multiport *multiinfo
		= (struct xt_multiport *)(*match)->data;

	switch (c) {
	case '1':
		xtables_check_inverse(optarg, &invert, &optind, 0, argv);
		proto = check_proto(pnum, invflags);
		multiinfo->count = parse_multi_ports(optarg,
						     multiinfo->ports, proto);
		multiinfo->flags = XT_MULTIPORT_SOURCE;
		break;

	case '2':
		xtables_check_inverse(optarg, &invert, &optind, 0, argv);
		proto = check_proto(pnum, invflags);
		multiinfo->count = parse_multi_ports(optarg,
						     multiinfo->ports, proto);
		multiinfo->flags = XT_MULTIPORT_DESTINATION;
		break;

	case '3':
		xtables_check_inverse(optarg, &invert, &optind, 0, argv);
		proto = check_proto(pnum, invflags);
		multiinfo->count = parse_multi_ports(optarg,
						     multiinfo->ports, proto);
		multiinfo->flags = XT_MULTIPORT_EITHER;
		break;
	}

	if (invert)
		xtables_error(PARAMETER_PROBLEM,
			   "multiport does not support invert");

	if (*flags)
		xtables_error(PARAMETER_PROBLEM,
			   "multiport can only have one option");
	*flags = 1;
	return 1;
}
