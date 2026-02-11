netlink_link_del_vmac(vrrp_rt *vrrp)
{
	int status = 1;

#ifdef _HAVE_VRRP_VMAC_
	struct {
		struct nlmsghdr n;
		struct ifinfomsg ifi;
		char buf[256];
	} req;

	if (!vrrp->ifp)
		return -1;

	memset(&req, 0, sizeof (req));

	req.n.nlmsg_len = NLMSG_LENGTH(sizeof (struct ifinfomsg));
	req.n.nlmsg_flags = NLM_F_REQUEST;
	req.n.nlmsg_type = RTM_DELLINK;
	req.ifi.ifi_family = AF_INET;
	req.ifi.ifi_index = vrrp->vmac_ifindex;

	if (netlink_talk(&nl_cmd, &req.n) < 0)
		status = -1;
#endif

	return status;
}
