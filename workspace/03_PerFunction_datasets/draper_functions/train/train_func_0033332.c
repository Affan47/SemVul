rtnl_rtntype_a2n(int *id, char *arg)
{
	static const char keywords[] ALIGN1 =
		"local\0""nat\0""broadcast\0""brd\0""anycast\0"
		"multicast\0""prohibit\0""unreachable\0""blackhole\0"
		"xresolve\0""unicast\0""throw\0";
	enum {
		ARG_local = 1, ARG_nat, ARG_broadcast, ARG_brd, ARG_anycast,
		ARG_multicast, ARG_prohibit, ARG_unreachable, ARG_blackhole,
		ARG_xresolve, ARG_unicast, ARG_throw
	};
	const smalluint key = index_in_substrings(keywords, arg) + 1;
	char *end;
	unsigned long res;

	if (key == ARG_local)
		res = RTN_LOCAL;
	else if (key == ARG_nat)
		res = RTN_NAT;
	else if (key == ARG_broadcast || key == ARG_brd)
		res = RTN_BROADCAST;
	else if (key == ARG_anycast)
		res = RTN_ANYCAST;
	else if (key == ARG_multicast)
		res = RTN_MULTICAST;
	else if (key == ARG_prohibit)
		res = RTN_PROHIBIT;
	else if (key == ARG_unreachable)
		res = RTN_UNREACHABLE;
	else if (key == ARG_blackhole)
		res = RTN_BLACKHOLE;
	else if (key == ARG_xresolve)
		res = RTN_XRESOLVE;
	else if (key == ARG_unicast)
		res = RTN_UNICAST;
	else if (key == ARG_throw)
		res = RTN_THROW;
	else {
		res = strtoul(arg, &end, 0);
		if (end == arg || *end || res > 255)
			return -1;
	}
	*id = res;
	return 0;
}
