socket_set_intern(int fd, int option, unsigned size,
	const char *type, bool shrink)
{
	unsigned old_len = 0;
	unsigned new_len = 0;
	socklen_t len;

	if (0 == size)
		return 0;

	size = (size + 1) & ~0x1U;

	len = sizeof(old_len);
	if (-1 == getsockopt(fd, SOL_SOCKET, option, &old_len, &len))
		g_warning("cannot read old %s buffer length on fd #%d: %m", type, fd);


#ifdef LINUX_SYSTEM
	old_len >>= 1;
#endif

	if (!shrink && old_len >= size) {
		if (GNET_PROPERTY(socket_debug) > 5)
			g_debug(
				"socket %s buffer on fd #%d NOT shrank to %u bytes (is %u)",
				type, fd, size, old_len);
		return old_len;
	}

	if (-1 == setsockopt(fd, SOL_SOCKET, option, &size, sizeof(size)))
		g_warning("cannot set new %s buffer length to %u on fd #%d: %m",
			type, size, fd);

	len = sizeof(new_len);
	if (-1 == getsockopt(fd, SOL_SOCKET, option, &new_len, &len))
		g_warning("cannot read new %s buffer length on fd #%d: %m", type, fd);

#ifdef LINUX_SYSTEM
	new_len >>= 1;
#endif

	if (GNET_PROPERTY(socket_debug) > 5)
		g_debug("socket %s buffer on fd #%d: %u -> %u bytes (now %u) %s",
			type, fd, old_len, size, new_len,
			(new_len == size) ? "OK" : "FAILED");

	return (new_len == size) ? new_len : old_len;
}
