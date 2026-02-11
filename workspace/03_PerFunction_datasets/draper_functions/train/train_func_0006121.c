iplink_have_newlink(void)
{
	struct {
		struct nlmsghdr		n;
		struct ifinfomsg	i;
		char			buf[1024];
	} req;

	if (have_rtnl_newlink < 0) {
		memset(&req, 0, sizeof(req));

		req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
		req.n.nlmsg_flags = NLM_F_REQUEST|NLM_F_ACK;
		req.n.nlmsg_type = RTM_NEWLINK;
		req.i.ifi_family = AF_UNSPEC;

		rtnl_send(&rth, &req.n, req.n.nlmsg_len);
		rtnl_listen(&rth, accept_msg, NULL);
	}
	return have_rtnl_newlink;
}
