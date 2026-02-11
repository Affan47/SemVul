report_nl_error(struct nlmsghdr *nlh) {
	struct nlmsgerr *err;
	err = NLMSG_DATA(nlh);
	if (err->error == 0)
		return;
	fprintf(stderr, "userui: Received netlink error: %s\n",
			strerror(-err->error));
	fprintf(stderr, "userui: This was in response to a type %d message.\n",
			err->msg.nlmsg_type);
}
