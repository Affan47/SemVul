flags2string(u_short flags)
{
	static char buf[256];

	buf[0] = '\0';

	if (flags & INTF_FLAG_UP)
		strlcat(buf, ",UP", sizeof(buf));
	if (flags & INTF_FLAG_LOOPBACK)
		strlcat(buf, ",LOOPBACK", sizeof(buf));
	if (flags & INTF_FLAG_POINTOPOINT)
		strlcat(buf, ",POINTOPOINT", sizeof(buf));
	if (flags & INTF_FLAG_NOARP)
		strlcat(buf, ",NOARP", sizeof(buf));
	if (flags & INTF_FLAG_BROADCAST)
		strlcat(buf, ",BROADCAST", sizeof(buf));
	if (flags & INTF_FLAG_MULTICAST)
		strlcat(buf, ",MULTICAST", sizeof(buf));

	if (buf[0] != '\0')
		return (buf + 1);

	return (buf);
}
