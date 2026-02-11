do_add(int cmd, int argc, char **argv)
{
	struct ip6_tnl_parm2 p;

	ip6_tnl_parm_init(&p, 1);

	if (parse_args(argc, argv, cmd, &p) < 0)
		return -1;

	switch (p.proto) {
	case IPPROTO_IPIP:
	case IPPROTO_IPV6:
		return tnl_add_ioctl(cmd, "ip6tnl0", p.name, &p);
	case IPPROTO_GRE:
		return tnl_add_ioctl(cmd, "ip6gre0", p.name, &p);
	default:
		fprintf(stderr, "cannot determine tunnel mode (ip6ip6, ipip6 or gre)\n");
	}
	return -1;
}
