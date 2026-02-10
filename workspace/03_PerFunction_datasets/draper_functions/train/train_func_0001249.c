rb_setselect_epoll(rb_fde_t *F, unsigned int type, PF * handler, void *client_data)
{
	struct epoll_event ep_event;
	int old_flags = F->pflags;
	int op = -1;

	lrb_assert(IsFDOpen(F));


	if(type & RB_SELECT_READ)
	{
		if(handler != NULL)
			F->pflags |= EPOLLIN;
		else
			F->pflags &= ~EPOLLIN;
		F->read_handler = handler;
		F->read_data = client_data;
	}

	if(type & RB_SELECT_WRITE)
	{
		if(handler != NULL)
			F->pflags |= EPOLLOUT;
		else
			F->pflags &= ~EPOLLOUT;
		F->write_handler = handler;
		F->write_data = client_data;
	}

	if(old_flags == 0 && F->pflags == 0)
		return;
	else if(F->pflags <= 0)
		op = EPOLL_CTL_DEL;
	else if(old_flags == 0 && F->pflags > 0)
		op = EPOLL_CTL_ADD;
	else if(F->pflags != old_flags)
		op = EPOLL_CTL_MOD;

	if(op == -1)
		return;

	ep_event.events = F->pflags;
	ep_event.data.ptr = F;

	if(op == EPOLL_CTL_ADD || op == EPOLL_CTL_MOD)
		ep_event.events |= EPOLLET;

	if(epoll_ctl(ep_info->ep, op, F->fd, &ep_event) != 0)
	{
		rb_lib_log("rb_setselect_epoll(): epoll_ctl failed: %s", strerror(errno));
		abort();
	}


}
