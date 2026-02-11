iplink_get_stats(int ifindex, struct rtnl_link_stats *stats)
{
	struct iplink_req {
		struct nlmsghdr n;
		struct ifinfomsg i;
		char buf[4096];
	} req;
	struct ifinfomsg *ifi;
	int len;
	struct rtattr *tb[IFLA_MAX + 1];

	if (!rth)
		open_rth();

	if (!rth)
		return -1;

	memset(&req, 0, sizeof(req) - 4096);

	req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	req.n.nlmsg_type = RTM_GETLINK;
	req.i.ifi_family = AF_PACKET;
	req.i.ifi_index = ifindex;

	if (rtnl_talk(rth, &req.n, 0, 0, &req.n, NULL, NULL, 0) < 0)
		return -1;

	if (req.n.nlmsg_type != RTM_NEWLINK)
		return -1;

	ifi = NLMSG_DATA(&req.n);

	len = req.n.nlmsg_len;

	len -= NLMSG_LENGTH(sizeof(*ifi));
	if (len < 0)
		return -1;

	parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);
	if (tb[IFLA_STATS])
		memcpy(stats, RTA_DATA(tb[IFLA_STATS]), sizeof(*stats));
	else
		return -1;

	return 0;
}
