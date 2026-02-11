intf_get_dst(intf_t *intf, struct intf_entry *entry, struct addr *dst)
{
	struct sockaddr_in sin;
	int n;

	if (dst->addr_type != ADDR_TYPE_IP) {
		errno = EINVAL;
		return (-1);
	}
	addr_ntos(dst, (struct sockaddr *)&sin);
	sin.sin_port = htons(666);

	if (connect(intf->fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);

	n = sizeof(sin);
	if (getsockname(intf->fd, (struct sockaddr *)&sin, &n) < 0)
		return (-1);

	addr_ston((struct sockaddr *)&sin, &entry->intf_addr);

	if (intf_loop(intf, _match_intf_src, entry) != 1)
		return (-1);

	return (0);
}
