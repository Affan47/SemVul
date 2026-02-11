init_address_list(private_kernel_netlink_net_t *this)
{
	netlink_buf_t request;
	struct nlmsghdr *out, *current, *in;
	struct rtgenmsg *msg;
	size_t len;
	enumerator_t *ifaces, *addrs;
	iface_entry_t *iface;
	addr_entry_t *addr;

	DBG2(DBG_KNL, "known interfaces and IP addresses:");

	memset(&request, 0, sizeof(request));

	in = &request.hdr;
	in->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtgenmsg));
	in->nlmsg_flags = NLM_F_REQUEST | NLM_F_MATCH | NLM_F_ROOT;
	msg = NLMSG_DATA(in);
	msg->rtgen_family = AF_UNSPEC;


	in->nlmsg_type = RTM_GETLINK;
	if (this->socket->send(this->socket, in, &out, &len) != SUCCESS)
	{
		return FAILED;
	}
	current = out;
	while (NLMSG_OK(current, len))
	{
		switch (current->nlmsg_type)
		{
			case NLMSG_DONE:
				break;
			case RTM_NEWLINK:
				process_link(this, current, FALSE);

			default:
				current = NLMSG_NEXT(current, len);
				continue;
		}
		break;
	}
	free(out);


	in->nlmsg_type = RTM_GETADDR;
	if (this->socket->send(this->socket, in, &out, &len) != SUCCESS)
	{
		return FAILED;
	}
	current = out;
	while (NLMSG_OK(current, len))
	{
		switch (current->nlmsg_type)
		{
			case NLMSG_DONE:
				break;
			case RTM_NEWADDR:
				process_addr(this, current, FALSE);

			default:
				current = NLMSG_NEXT(current, len);
				continue;
		}
		break;
	}
	free(out);

	this->lock->read_lock(this->lock);
	ifaces = this->ifaces->create_enumerator(this->ifaces);
	while (ifaces->enumerate(ifaces, &iface))
	{
		if (iface_entry_up_and_usable(iface))
		{
			DBG2(DBG_KNL, "  %s", iface->ifname);
			addrs = iface->addrs->create_enumerator(iface->addrs);
			while (addrs->enumerate(addrs, (void**)&addr))
			{
				DBG2(DBG_KNL, "    %H", addr->ip);
			}
			addrs->destroy(addrs);
		}
	}
	ifaces->destroy(ifaces);
	this->lock->unlock(this->lock);
	return SUCCESS;
}
