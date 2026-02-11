wxt_waitforinput()
{


	if (wxt_status == STATUS_UNINITIALIZED)
		return getc(stdin);

	if (wxt_event_fd<0) {
		if (paused_for_mouse)
			int_error(NO_CARET, "wxt communication error, wxt_event_fd<0");
		FPRINTF((stderr,"wxt communication error, wxt_event_fd<0\n"));
		return getc(stdin);
	}

	int stdin_fd = fileno(stdin);
	fd_set read_fds;

	do {
		FD_ZERO(&read_fds);
		FD_SET(wxt_event_fd, &read_fds);
		if (!paused_for_mouse)
			FD_SET(stdin_fd, &read_fds);

		int n_changed_fds = select(wxt_event_fd+1, &read_fds,
					      NULL ,
					      NULL ,
					      NULL );

		if (n_changed_fds<0) {
			if (paused_for_mouse)
				int_error(NO_CARET, "wxt communication error: select() error");
			FPRINTF((stderr, "wxt communication error: select() error\n"));
			break;
		}

		if (FD_ISSET(wxt_event_fd, &read_fds)) {

			struct gp_event_t wxt_event;
			int n_bytes_read = read(wxt_event_fd, (void*) &wxt_event, sizeof(wxt_event));
			if (n_bytes_read < (int)sizeof(wxt_event)) {
				if (paused_for_mouse)
					int_error(NO_CARET, "wxt communication error, not enough bytes read");
				FPRINTF((stderr, "wxt communication error, not enough bytes read\n"));
				break;
			}
			if (wxt_process_one_event(&wxt_event)) {

				return '\0';
			}
		}
	} while ( paused_for_mouse
		   || (!paused_for_mouse && !FD_ISSET(stdin_fd, &read_fds)) );

	return getchar();
}
