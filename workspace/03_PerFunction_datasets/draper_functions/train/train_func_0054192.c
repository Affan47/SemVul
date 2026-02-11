iplink_vlan_add(const char *ifname, int ifindex, int vid)
{
	struct iplink_req {
		struct nlmsghdr n;
		struct ifinfomsg i;
		char buf[4096];
	} req;
	struct rtattr *linkinfo, *data;

	if (!rth)
		open_rth();

	if (!rth)
		return -1;

	memset(&req, 0, sizeof(req) - 4096);

	req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK | NLM_F_CREATE | NLM_F_EXCL;
	req.n.nlmsg_type = RTM_NEWLINK;
	req.i.ifi_family = AF_UNSPEC;

	addattr_l(&req.n, 4096, IFLA_LINK, &ifindex, 4);
	addattr_l(&req.n, 4096, IFLA_IFNAME, ifname, strlen(ifname));

	linkinfo = NLMSG_TAIL(&req.n);
	addattr_l(&req.n, 4096, IFLA_LINKINFO, NULL, 0);
	addattr_l(&req.n, 4096, IFLA_INFO_KIND, "vlan", 4);

	data = NLMSG_TAIL(&req.n);
	addattr_l(&req.n, 4096, IFLA_INFO_DATA, NULL, 0);
	addattr_l(&req.n, 4096, IFLA_VLAN_ID, &vid, 2);
	data->rta_len = (void *)NLMSG_TAIL(&req.n) - (void *)data;

	linkinfo->rta_len = (void *)NLMSG_TAIL(&req.n) - (void *)linkinfo;

	if (rtnl_talk(rth, &req.n, 0, 0, NULL, NULL, NULL, 0) < 0)
		return -1;

	return 0;
}
