socket_set_reusable(evutil_socket_t fd, int flag)
{

	if (fd < 0)
		return -1;
	else {

#if defined(WIN32)
		int use_reuseaddr = IS_TURN_SERVER;
#else
		int use_reuseaddr = 1;
#endif

#if defined(SO_REUSEPORT)
		if (use_reuseaddr) {
			int on = flag;
			setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const void*) &on, (socklen_t) sizeof(on));
		}
#endif

#if defined(SO_REUSEADDR)
		if (use_reuseaddr) {
			int on = flag;
			int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void*) &on, (socklen_t) sizeof(on));
			if (ret < 0)
				perror("SO_REUSEADDR");
		}
#endif

		return 0;
	}
}
