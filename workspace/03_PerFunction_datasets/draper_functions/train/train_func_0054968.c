iface_fill_mtu(struct iovec *iov, struct iface_rec *iface,
			  uint32_t iface_type)
{
	int len;
	struct iscsi_iface_param_info *net_param;
	uint16_t mtu = 0;
	struct nlattr *attr;

	len = sizeof(struct iscsi_iface_param_info) + 2;
	iov->iov_base = iscsi_nla_alloc(ISCSI_NET_PARAM_MTU, len);
	if (!(iov->iov_base))
		return 1;
	attr = iov->iov_base;
	iov->iov_len = NLA_ALIGN(attr->nla_len);

	net_param = (struct iscsi_iface_param_info *)ISCSI_NLA_DATA(attr);
	net_param->param = ISCSI_NET_PARAM_MTU;
	net_param->iface_type = iface_type;
	net_param->iface_num = iface->iface_num;
	net_param->param_type = ISCSI_NET_PARAM;
	net_param->len = 2;
	mtu = iface->mtu;
	memcpy(net_param->value, &mtu, net_param->len);
	return 0;
}
