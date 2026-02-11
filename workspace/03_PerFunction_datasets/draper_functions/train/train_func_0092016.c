epoll_dealloc(struct event_base *base)
{
	struct epollop *epollop = base->evbase;

	evsig_dealloc_(base);
	if (epollop->events)
		mm_free(epollop->events);
	if (epollop->epfd >= 0)
		close(epollop->epfd);
#ifdef USING_TIMERFD
	if (epollop->timerfd >= 0)
		close(epollop->timerfd);
#endif

	memset(epollop, 0, sizeof(struct epollop));
	mm_free(epollop);
}
