getch_nowait(void)
{
	int rd;
	struct pollfd pfd[2];

	pfd[0].fd = STDIN_FILENO;
	pfd[0].events = POLLIN;
	pfd[1].fd = kbd_fd;
	pfd[1].events = POLLIN;
 again:
	tcsetattr(kbd_fd, TCSANOW, &term_less);


	rd = 1;


	if (!(option_mask32 & FLAG_S)
	   ? !(max_fline > cur_fline + max_displayed_line)
	   : !(max_fline >= cur_fline
	       && max_lineno > LINENO(flines[cur_fline]) + max_displayed_line)
	) {
		if (eof_error > 0)
			rd = 0;
	}

	if (less_gets_pos >= 0)
		move_cursor(max_displayed_line + 2, less_gets_pos + 1);
	fflush_all();

	if (kbd_input[0] == 0) {
#if ENABLE_FEATURE_LESS_WINCH
		while (1) {
			int r;

			r = poll(pfd + rd, 2 - rd, -1);
			if ( winch_counter)
				return '\\';
			if (r) break;
		}
#else
		safe_poll(pfd + rd, 2 - rd, -1);
#endif
	}


	rd = read_key(kbd_fd, kbd_input,  -2);
	if (rd == -1) {
		if (errno == EAGAIN) {


			read_lines();
			buffer_fill_and_print();
			goto again;
		}

		less_exit(0);
	}
	set_tty_cooked();
	return rd;
}
