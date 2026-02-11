source_dispatch(G_GNUC_UNUSED GSource *source,
	G_GNUC_UNUSED GSourceFunc callback, G_GNUC_UNUSED gpointer gdata)
{
	int status;
	pid_t result;
	ssize_t count;
	char buffer[0x200];
	char *pos;


	while ((count = read(gdb_err.fd, buffer, sizeof buffer - 1)) > 0)
		dc_output(2, buffer, count);

	gdb_io_check(count, "read(gdb_err)", EINVAL);


	count = read(gdb_out.fd, received->str + received->len, MAXLEN - received->len);

	if (count > 0)
		g_string_set_size(received, received->len + count);
	else
		gdb_io_check(count, "read(gdb_out)", EINVAL);

	while (pos = reading_pos, (reading_pos = strchr(pos, '\n')) != NULL)
	{
		if (leading_receive)
		{
		#ifdef G_OS_UNIX
			*reading_pos++ = '\0';
		#else
			gboolean cr = reading_pos > received->str && reading_pos[-1] == '\r';
			reading_pos[-cr]= '\0';
			reading_pos++;
		#endif
			pre_parse(pos, FALSE);
		}
		else
		{
			reading_pos++;
			leading_receive = FALSE;
		}
	}

	g_string_erase(received, 0, pos - received->str);

	if (G_UNLIKELY(received->len == MAXLEN))
	{
		if (leading_receive)
		{
			reading_pos = received->str + MAXLEN;
			pre_parse(received->str, TRUE);
		}
		g_string_truncate(received, 0);
		leading_receive = FALSE;
	}

	reading_pos = received->str;
 	result = waitpid(gdb_pid, &status, WNOHANG);

	if (result == 0)
	{
		if (commands->len)
		{

		#ifdef G_OS_UNIX
			send_commands();
			if (!commands->len)
				g_source_remove_poll(gdb_source, &gdb_in);
		#else
			debug_send_commands();
		#endif
		}
		else
		{

			DebugState state = debug_state();

			if (state & DS_SENDABLE)
				views_update(state);
		}
	}
	else if (gdb_state != INACTIVE)
	{
		GdbState state = gdb_state;

		gdb_state = INACTIVE;
		signal(SIGINT, SIG_DFL);
		g_source_remove(source_id);

		if (result == -1)
			show_errno("waitpid(gdb)");
		else if (state == ACTIVE)
			show_error(_("GDB died unexpectedly with status %d."), status);
		else if (thread_count)
			ui_set_statusbar(FALSE, _("Program terminated."));

		free_gdb();
		views_clear();
		utils_lock_all(FALSE);
	}

	update_state(debug_state());

	return TRUE;
}
