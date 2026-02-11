e2_fs_get_command_output (gchar *command, gpointer *output)
{
	gchar *local = F_FILENAME_TO_LOCALE (command);
	E2_FILE *pipe = e2_fs_open_pipe (local);
	F_FREE (local);
	if (pipe == NULL)
		return FALSE;
	gchar *msg = g_strdup_printf (
			_("Command %s failed: not enough memory"), command);
	size_t total = 0;
	size_t bsize = 4096;
	gpointer buf = g_try_malloc ((gulong) bsize);
	if (buf == NULL)
	{
		e2_output_print_error (msg, TRUE);
		e2_fs_pipe_close (pipe);
		return FALSE;
	}
	gpointer store = buf;
	ssize_t bytes_read;
	while ((bytes_read = fread (store, 1, bsize, pipe)) > 0)
	{
		if (bytes_read == bsize)
		{
			total += bsize;
			buf = g_try_realloc (buf, total+bsize);
			if (buf == NULL)
			{
				e2_output_print_error (msg, TRUE);
				e2_fs_pipe_close (pipe);
				return FALSE;
			}
			store = buf + total;
		}
		else
		{
			*((gchar *)store+bytes_read) = '\0';
			bytes_read++;
			total += bytes_read;
			buf = g_try_realloc (buf, total);
			if (buf == NULL)
			{
				e2_output_print_error (msg, TRUE);
				e2_fs_pipe_close (pipe);
				return FALSE;
			}
			break;
		}
	}

	g_free (msg);
	e2_fs_pipe_close (pipe);
	if (total == 0)
		g_free (buf);
	else
		*output = buf;
	return (total > 0);
}
