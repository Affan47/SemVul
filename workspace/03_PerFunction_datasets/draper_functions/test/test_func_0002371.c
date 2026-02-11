guess_local_addr(const struct gnutella_socket *s)
{
	host_addr_t addr;

	if (socket_local_addr(s, &addr)) {
		switch (host_addr_net(addr)) {
		case NET_TYPE_IPV4:
		case NET_TYPE_IPV6:
			settings_addr_changed(addr, s->addr);
			break;
		case NET_TYPE_LOCAL:
		case NET_TYPE_NONE:
			break;
		}
	}
}
