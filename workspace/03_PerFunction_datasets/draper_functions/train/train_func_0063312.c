vty_event(event_t event, int sock, vty_t *vty)
{
	thread_t *vty_serv_thread;

	switch (event) {
	case VTY_SERV:
		vty_serv_thread = thread_add_read(master, vty_accept, vty, sock,
						  VTY_IO_TIMEOUT);
		vector_set_index(Vvty_serv_thread, sock, vty_serv_thread);
		break;

	case VTY_READ:
		vty->t_read = thread_add_read(master, vty_read, vty, sock, VTY_IO_TIMEOUT);


		if (vty->v_timeout) {
			if (vty->t_timeout)
				thread_cancel(vty->t_timeout);
			vty->t_timeout = thread_add_timer(master, vty_timeout, vty,
							  vty->v_timeout*TIMER_HZ);
		}
		break;

	case VTY_WRITE:
		if (!vty->t_write)
			vty->t_write = thread_add_write(master, vty_flush, vty, sock,
							VTY_IO_TIMEOUT);
		break;

	case VTY_TIMEOUT_RESET:
		if (vty->t_timeout) {
			thread_cancel(vty->t_timeout);
			vty->t_timeout = NULL;
		}

		if (vty->v_timeout) {
			vty->t_timeout = thread_add_timer(master, vty_timeout, vty,
							  vty->v_timeout*TIMER_HZ);
		}
		break;
	}
}
