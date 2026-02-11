socket_addr_getpeername(socket_addr_t *p_addr, int fd)
{
	socklen_t addr_len;

	g_return_val_if_fail(p_addr, -1);
	g_return_val_if_fail(fd >= 0, -1);

	errno = 0;
	addr_len = socket_addr_init(p_addr, NET_TYPE_IPV4);
	if (
		-1 != getpeername(fd, socket_addr_get_sockaddr(p_addr), &addr_len) &&
		AF_INET == socket_addr_get_family(p_addr)
	) {
		return 0;
	}

#ifdef HAS_IPV6
	errno = 0;
	addr_len = socket_addr_init(p_addr, NET_TYPE_IPV6);
	if (
		-1 != getpeername(fd, socket_addr_get_sockaddr(p_addr), &addr_len) &&
		AF_INET6 == socket_addr_get_family(p_addr)
	) {
		return 0;
	}
#endif

	return -1;
}
