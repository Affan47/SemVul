parse_ports(const char *arg, struct nf_nat_range *r)
{
	char *end;
	unsigned int port, maxport;

	r->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;

	if (!xtables_strtoui(arg, &end, &port, 0, UINT16_MAX))
		xtables_param_act(XTF_BAD_VALUE, "MASQUERADE", "--to-ports", arg);

	switch (*end) {
	case '\0':
		r->min_proto.tcp.port
			= r->max_proto.tcp.port
			= htons(port);
		return;
	case '-':
		if (!xtables_strtoui(end + 1, NULL, &maxport, 0, UINT16_MAX))
			break;

		if (maxport < port)
			break;

		r->min_proto.tcp.port = htons(port);
		r->max_proto.tcp.port = htons(maxport);
		return;
	default:
		break;
	}
	xtables_param_act(XTF_BAD_VALUE, "MASQUERADE", "--to-ports", arg);
}
