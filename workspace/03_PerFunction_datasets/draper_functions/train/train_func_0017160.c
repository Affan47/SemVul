parse_nexthops(struct nlmsghdr *n, struct rtmsg *r, int argc, char **argv)
{
	char buf[1024];
	struct rtattr *rta = (void*)buf;
	struct rtnexthop *rtnh;

	rta->rta_type = RTA_MULTIPATH;
	rta->rta_len = RTA_LENGTH(0);
	rtnh = RTA_DATA(rta);

	while (argc > 0) {
		if (strcmp(*argv, "nexthop") != 0) {
			fprintf(stderr, "Error: \"nexthop\" or end of line is expected instead of \"%s\"\n", *argv);
			exit(-1);
		}
		if (argc <= 1) {
			fprintf(stderr, "Error: unexpected end of line after \"nexthop\"\n");
			exit(-1);
		}
		memset(rtnh, 0, sizeof(*rtnh));
		rtnh->rtnh_len = sizeof(*rtnh);
		rta->rta_len += rtnh->rtnh_len;
		parse_one_nh(rta, rtnh, &argc, &argv);
		rtnh = RTNH_NEXT(rtnh);
	}

	if (rta->rta_len > RTA_LENGTH(0))
		addattr_l(n, 1024, RTA_MULTIPATH, RTA_DATA(rta), RTA_PAYLOAD(rta));
	return 0;
}
