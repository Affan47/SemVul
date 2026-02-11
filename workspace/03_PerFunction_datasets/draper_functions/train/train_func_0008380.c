ipvs_mt_parse(int c, char **argv, int invert, unsigned int *flags,
			 const void *entry, struct xt_entry_match **match,
			 unsigned int family)
{
	struct xt_ipvs_mtinfo *data = (void *)(*match)->data;
	char *p = NULL;
	uint8_t op = 0;

	if ('0' <= c && c <= '6') {
		static const int ops[] = {
			XT_IPVS_IPVS_PROPERTY,
			XT_IPVS_PROTO,
			XT_IPVS_VADDR,
			XT_IPVS_VPORT,
			XT_IPVS_DIR,
			XT_IPVS_METHOD,
			XT_IPVS_VPORTCTL
		};
		op = ops[c - '0'];
	} else
		return 0;

	if (*flags & op & XT_IPVS_ONCE_MASK)
		goto multiple_use;

	switch (c) {
	case '0':

		break;

	case '1':

		for (p = optarg; *p != '\0'; ++p)
			*p = tolower(*p);

		data->l4proto = xtables_parse_protocol(optarg);
		break;

	case '2':
		ipvs_mt_parse_addr_and_mask(optarg, &data->vaddr,
					    &data->vmask, family);
		break;

	case '3':
		data->vport = htons(xtables_parse_port(optarg, "tcp"));
		break;

	case '4':
		xtables_param_act(XTF_NO_INVERT, "ipvs", "--vdir", invert);
		if (strcasecmp(optarg, "ORIGINAL") == 0) {
			data->bitmask |= XT_IPVS_DIR;
			data->invert   &= ~XT_IPVS_DIR;
		} else if (strcasecmp(optarg, "REPLY") == 0) {
			data->bitmask |= XT_IPVS_DIR;
			data->invert  |= XT_IPVS_DIR;
		} else {
			xtables_param_act(XTF_BAD_VALUE,
					  "ipvs", "--vdir", optarg);
		}
		break;

	case '5':
		if (strcasecmp(optarg, "GATE") == 0)
			data->fwd_method = IP_VS_CONN_F_DROUTE;
		else if (strcasecmp(optarg, "IPIP") == 0)
			data->fwd_method = IP_VS_CONN_F_TUNNEL;
		else if (strcasecmp(optarg, "MASQ") == 0)
			data->fwd_method = IP_VS_CONN_F_MASQ;
		else
			xtables_param_act(XTF_BAD_VALUE,
					  "ipvs", "--vmethod", optarg);
		break;

	case '6':
		data->vportctl = htons(xtables_parse_port(optarg, "tcp"));
		break;
	}

	if (op & XT_IPVS_ONCE_MASK) {
		if (data->invert & XT_IPVS_IPVS_PROPERTY)
			xtables_error(PARAMETER_PROBLEM,
				      "! --ipvs cannot be together with"
				      " other options");
		data->bitmask |= XT_IPVS_IPVS_PROPERTY;
	}

	data->bitmask |= op;
	if (invert)
		data->invert |= op;
	*flags |= op;
	return 1;

multiple_use:
	xtables_error(PARAMETER_PROBLEM,
		      "multiple use of the same IPVS option is not allowed");
}
