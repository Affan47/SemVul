evthread_notify_base_default(struct event_base *base)
{
	char buf[1];
	int r;
	buf[0] = (char) 0;
#ifdef WIN32
	r = send(base->th_notify_fd[1], buf, 1, 0);
#else
	r = write(base->th_notify_fd[1], buf, 1);
#endif
	return (r < 0 && errno != EAGAIN) ? -1 : 0;
}
