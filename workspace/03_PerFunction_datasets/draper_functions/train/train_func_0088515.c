evthread_notify_base_default(struct event_base *base)
{
	char buf[1];
	int r;
	buf[0] = (char) 0;
#ifdef _WIN32
	r = send(base->th_notify_fd[1], buf, 1, 0);
#else
	r = write(base->th_notify_fd[1], buf, 1);
#endif
	return (r < 0 && ! EVUTIL_ERR_IS_EAGAIN(errno)) ? -1 : 0;
}
