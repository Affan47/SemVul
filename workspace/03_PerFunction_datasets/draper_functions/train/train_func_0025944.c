accept_msg(const struct sockaddr_nl *who,
		      struct nlmsghdr *n, void *arg)
{
	struct nlmsgerr *err = (struct nlmsgerr *)NLMSG_DATA(n);

	if (n->nlmsg_type == NLMSG_ERROR &&
	    (err->error == -EOPNOTSUPP || err->error == -EINVAL))
		have_rtnl_newlink = 0;
	else
		have_rtnl_newlink = 1;
	return -1;
}
