do_show(char **argv)
{
	int err;
	struct ip_tunnel_parm p;

	parse_args(argv, SIOCGETTUNNEL, &p);

	switch (p.iph.protocol) {
	case IPPROTO_IPIP:
		err = do_get_ioctl(p.name[0] ? p.name : "tunl0", &p);
		break;
	case IPPROTO_GRE:
		err = do_get_ioctl(p.name[0] ? p.name : "gre0", &p);
		break;
	case IPPROTO_IPV6:
		err = do_get_ioctl(p.name[0] ? p.name : "sit0", &p);
		break;
	default:
		do_tunnels_list(&p);
		return 0;
	}
	if (err)
		return -1;

	print_tunnel(&p);
	bb_putchar('\n');
	return 0;
}
