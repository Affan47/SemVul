rb_accept_tryaccept(rb_fde_t *F, void *data)
{
	struct rb_sockaddr_storage st;
	rb_fde_t *new_F;
	rb_socklen_t addrlen = sizeof(st);
	int new_fd;

	while(1)
	{
		new_fd = accept(F->fd, (struct sockaddr *)&st, &addrlen);
		rb_get_errno();
		if(new_fd < 0)
		{
			rb_setselect(F, RB_SELECT_ACCEPT, rb_accept_tryaccept, NULL);
			return;
		}

		rb_fd_hack(&new_fd);

		new_F = rb_open(new_fd, RB_FD_SOCKET, "Incoming Connection");

		if(new_F == NULL)
		{
			rb_lib_log
				("rb_accept: new_F == NULL on incoming connection. Closing new_fd == %d\n",
				 new_fd);
			close(new_fd);
			continue;
		}

		if(rb_unlikely(!rb_set_nb(new_F)))
		{
			rb_get_errno();
			rb_lib_log("rb_accept: Couldn't set FD %d non blocking!", new_F->fd);
			rb_close(new_F);
		}

#ifdef RB_IPV6
		mangle_mapped_sockaddr((struct sockaddr *)&st);
#endif

		if(F->accept->precb != NULL)
		{
			if(!F->accept->precb(new_F, (struct sockaddr *)&st, addrlen, F->accept->data))
				continue;
		}
#ifdef HAVE_SSL
		if(F->type & RB_FD_SSL)
		{
			rb_ssl_accept_setup(F, new_F, (struct sockaddr *)&st, addrlen);
		}
		else
#endif
		{
			F->accept->callback(new_F, RB_OK, (struct sockaddr *)&st, addrlen,
					    F->accept->data);
		}
	}

}
