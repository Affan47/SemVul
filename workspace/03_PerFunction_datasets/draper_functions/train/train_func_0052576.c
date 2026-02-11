xfrm_policy_flush(int argc, char **argv)
{
	struct rtnl_handle rth;
	struct {
		struct nlmsghdr	n;
		char		buf[RTA_BUF_SIZE];
	} req;
	char *ptypep = NULL;
	struct xfrm_userpolicy_type upt;

	memset(&req, 0, sizeof(req));
	memset(&upt, 0, sizeof(upt));

	req.n.nlmsg_len = NLMSG_LENGTH(0);
	req.n.nlmsg_flags = NLM_F_REQUEST;
	req.n.nlmsg_type = XFRM_MSG_FLUSHPOLICY;

	while (argc > 0) {
		if (strcmp(*argv, "ptype") == 0) {
			if (ptypep)
				duparg("ptype", *argv);
			ptypep = *argv;

			NEXT_ARG();
			xfrm_policy_ptype_parse(&upt.type, &argc, &argv);
		} else
			invarg("unknown", *argv);

		argc--; argv++;
	}

	if (ptypep) {
		addattr_l(&req.n, sizeof(req), XFRMA_POLICY_TYPE,
			  (void *)&upt, sizeof(upt));
	}

	if (rtnl_open_byproto(&rth, 0, NETLINK_XFRM) < 0)
		exit(1);

	if (show_stats > 1)
		fprintf(stderr, "Flush policy\n");

	if (rtnl_talk(&rth, &req.n, 0, 0, NULL) < 0)
		exit(2);

	rtnl_close(&rth);

	return 0;
}
