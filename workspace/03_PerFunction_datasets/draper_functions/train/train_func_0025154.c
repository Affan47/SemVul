iprange_parse_range(char *arg, union nf_inet_addr *range,
				uint8_t family, const char *optname)
{
	char *dash;

	dash = strchr(arg, '-');
	if (dash == NULL) {
		iprange_parse_spec(arg, arg, range, family, optname);
		return;
	}

	*dash = '\0';
	iprange_parse_spec(arg, dash + 1, range, family, optname);
	if (memcmp(&range[0], &range[1], sizeof(*range)) > 0)
		fprintf(stderr, "xt_iprange: range %s-%s is reversed and "
			"will never match\n", arg, dash + 1);
}
