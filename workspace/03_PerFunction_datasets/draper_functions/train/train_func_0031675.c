on_tar_listed (GPid pid,
				gint status,
				gpointer data)
{
	NPWTarPacket *pack = (NPWTarPacket *)data;

	if (pack->callback != NULL)
	{
		GIOChannel *output;
		GList *list;
		GString *line;
		GIOStatus status;

		list = NULL;
		line = g_string_new (NULL);
		output = g_io_channel_unix_new (pack->stdout);
		do
		{
			gsize terminator;

			status = g_io_channel_read_line_string (output, line, &terminator, NULL);
			if (status == G_IO_STATUS_NORMAL)
			{
				g_string_truncate (line, terminator);

				list = g_list_prepend (list, g_strdup (line->str));
				continue;
			}
		}
		while (status == G_IO_STATUS_AGAIN);
		g_io_channel_shutdown (output, TRUE, NULL);
		g_io_channel_unref (output);
		g_string_free (line, TRUE);

		list = g_list_reverse (list);
		((NPWTarListFunc)pack->callback) (pack->tarfile, list, pack->data, NULL);

		g_list_foreach (list, (GFunc)g_free, NULL);
		g_list_free (list);
	}

	g_spawn_close_pid(pid);
}
