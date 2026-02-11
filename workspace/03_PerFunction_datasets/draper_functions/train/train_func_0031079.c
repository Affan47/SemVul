xfrm_policy_keep(const struct sockaddr_nl *who,
			    struct nlmsghdr *n,
			    void *arg)
{
	struct xfrm_buffer *xb = (struct xfrm_buffer *)arg;
	struct rtnl_handle *rth = xb->rth;
	struct xfrm_userpolicy_info *xpinfo = NLMSG_DATA(n);
	int len = n->nlmsg_len;
	struct rtattr *tb[XFRMA_MAX+1];
	__u8 ptype = XFRM_POLICY_TYPE_MAIN;
	struct nlmsghdr *new_n;
	struct xfrm_userpolicy_id *xpid;

	if (n->nlmsg_type != XFRM_MSG_NEWPOLICY) {
		fprintf(stderr, "Not a policy: %08x %08x %08x\n",
			n->nlmsg_len, n->nlmsg_type, n->nlmsg_flags);
		return 0;
	}

	len -= NLMSG_LENGTH(sizeof(*xpinfo));
	if (len < 0) {
		fprintf(stderr, "BUG: wrong nlmsg len %d\n", len);
		return -1;
	}

	parse_rtattr(tb, XFRMA_MAX, XFRMP_RTA(xpinfo), len);

	if (tb[XFRMA_POLICY_TYPE]) {
		struct xfrm_userpolicy_type *upt;

		if (RTA_PAYLOAD(tb[XFRMA_POLICY_TYPE]) < sizeof(*upt)) {
			fprintf(stderr, "too short XFRMA_POLICY_TYPE len\n");
			return -1;
		}
		upt = (struct xfrm_userpolicy_type *)RTA_DATA(tb[XFRMA_POLICY_TYPE]);
		ptype = upt->type;
	}

	if (!xfrm_policy_filter_match(xpinfo, ptype))
		return 0;

	if (xb->offset > xb->size) {
		fprintf(stderr, "Policy buffer overflow\n");
		return -1;
	}

	new_n = (struct nlmsghdr *)(xb->buf + xb->offset);
	new_n->nlmsg_len = NLMSG_LENGTH(sizeof(*xpid));
	new_n->nlmsg_flags = NLM_F_REQUEST;
	new_n->nlmsg_type = XFRM_MSG_DELPOLICY;
	new_n->nlmsg_seq = ++rth->seq;

	xpid = NLMSG_DATA(new_n);
	memcpy(&xpid->sel, &xpinfo->sel, sizeof(xpid->sel));
	xpid->dir = xpinfo->dir;
	xpid->index = xpinfo->index;

	xb->offset += new_n->nlmsg_len;
	xb->nlmsg_count ++;

	return 0;
}
