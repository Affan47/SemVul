send_mapinfo_num(u32 mapping_num, u8 nl_client, int iwpm_pid)
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh;
	u32 msg_seq;
	const char *err_str = "";
	int ret = -EINVAL;

	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_MAPINFO_NUM, &nlh, nl_client);
	if (!skb) {
		err_str = "Unable to create a nlmsg";
		goto mapinfo_num_error;
	}
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	msg_seq = 0;
	err_str = "Unable to put attribute of mapinfo number nlmsg";
	ret = ibnl_put_attr(skb, nlh, sizeof(u32), &msg_seq, IWPM_NLA_MAPINFO_SEQ);
	if (ret)
		goto mapinfo_num_error;
	ret = ibnl_put_attr(skb, nlh, sizeof(u32),
				&mapping_num, IWPM_NLA_MAPINFO_SEND_NUM);
	if (ret)
		goto mapinfo_num_error;
	ret = ibnl_unicast(skb, nlh, iwpm_pid);
	if (ret) {
		skb = NULL;
		err_str = "Unable to send a nlmsg";
		goto mapinfo_num_error;
	}
	pr_debug("%s: Sent mapping number = %d\n", __func__, mapping_num);
	return 0;
mapinfo_num_error:
	pr_info("%s: %s\n", __func__, err_str);
	if (skb)
		dev_kfree_skb(skb);
	return ret;
}
