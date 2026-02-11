add_port_bypass(private_kernel_netlink_ipsec_t *this,
							int fd, int family)
{
	union {
		struct sockaddr sa;
		struct sockaddr_in in;
		struct sockaddr_in6 in6;
	} saddr;
	socklen_t len;
	bypass_t bypass = {
		.family = family,
	};

	len = sizeof(saddr);
	if (getsockname(fd, &saddr.sa, &len) != 0)
	{
		return FALSE;
	}
#ifdef SO_PROTOCOL
	len = sizeof(bypass.proto);
	if (getsockopt(fd, SOL_SOCKET, SO_PROTOCOL, &bypass.proto, &len) != 0)
#endif
	{
		bypass.proto = IPPROTO_UDP;
	}
	switch (family)
	{
		case AF_INET:
			bypass.port = saddr.in.sin_port;
			break;
		case AF_INET6:
			bypass.port = saddr.in6.sin6_port;
			break;
		default:
			return FALSE;
	}

	if (!manage_bypass(this, XFRM_MSG_NEWPOLICY, POLICY_IN, &bypass))
	{
		return FALSE;
	}
	if (!manage_bypass(this, XFRM_MSG_NEWPOLICY, POLICY_OUT, &bypass))
	{
		manage_bypass(this, XFRM_MSG_DELPOLICY, POLICY_IN, &bypass);
		return FALSE;
	}
	array_insert(this->bypass, ARRAY_TAIL, &bypass);

	return TRUE;
}
