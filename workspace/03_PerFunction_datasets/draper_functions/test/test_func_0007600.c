evthread_notify_drain_default(evutil_socket_t fd, short what, void *arg)
{
	unsigned char buf[128];
#ifdef WIN32
	while (recv(fd, (char*)buf, sizeof(buf), 0) > 0)
		;
#else
	while (read(fd, (char*)buf, sizeof(buf)) > 0)
		;
#endif
}
