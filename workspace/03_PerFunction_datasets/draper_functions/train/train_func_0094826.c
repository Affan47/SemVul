read_and_queue(private_netlink_socket_t *this, bool block)
{
	struct nlmsghdr *hdr;
	union {
		struct nlmsghdr hdr;
		char bytes[4096];
	} buf;
	ssize_t len;

	len = read_msg(this, buf.bytes, sizeof(buf.bytes), block);
	if (len == -1)
	{
		return TRUE;
	}
	if (len)
	{
		hdr = &buf.hdr;
		while (NLMSG_OK(hdr, len))
		{
			if (!queue(this, hdr))
			{
				break;
			}
			hdr = NLMSG_NEXT(hdr, len);
		}
	}
	return FALSE;
}
