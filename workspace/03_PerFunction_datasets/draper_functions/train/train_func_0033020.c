ipoe_nl_del_vlan_mon(int ifindex)
{
	struct nlmsghdr *nlh;
	struct genlmsghdr *ghdr;
	struct {
		struct nlmsghdr n;
		char buf[1024];
	} req;

	if (rth.fd == -1)
		return -1;

	nlh = &req.n;
	nlh->nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	nlh->nlmsg_type = ipoe_genl_id;

	ghdr = NLMSG_DATA(&req.n);
	ghdr->cmd = IPOE_CMD_DEL_VLAN_MON;

	addattr32(nlh, 1024, IPOE_ATTR_IFINDEX, ifindex);

	if (rtnl_talk(&rth, nlh, 0, 0, nlh, NULL, NULL, 0) < 0 ) {
		log_error("ipoe: nl_del_vlan_mon: error talking to kernel\n");
		return -1;
	}

	return 0;
}
