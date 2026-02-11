_do_register(void)
{
	struct poller *p;

	if (nbpollers >= MAX_POLLERS)
		return;

	epoll_fd = -1;
	p = &pollers[nbpollers++];

	p->name = "epoll";
	p->pref = 300;
	p->private = NULL;

	p->clo  = __fd_clo;
	p->test = _do_test;
	p->init = _do_init;
	p->term = _do_term;
	p->poll = _do_poll;
	p->fork = _do_fork;
}
