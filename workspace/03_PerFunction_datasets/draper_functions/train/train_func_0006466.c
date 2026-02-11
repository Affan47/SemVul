on_read_async_output(GIOChannel * src, GIOCondition cond, gpointer data)
{
	gchar *line;
	gsize length;

	if (G_IO_STATUS_NORMAL != g_io_channel_read_line(src, &line, NULL, &length, NULL))
		return TRUE;

	*(line + length) = '\0';

	if ('^' == line[0])
	{


		GList *lines;
		GList *commands = (GList*)data;
		gchar *coma;

		g_source_remove(gdb_id_out);

		lines = read_until_prompt();
		g_list_foreach(lines, (GFunc)g_free, NULL);
		g_list_free (lines);

		coma = strchr(line, ',');
		if (coma)
		{
			*coma = '\0';
			coma++;
		}
		else
			coma = line + strlen(line);

		if (!strcmp(line, "^done"))
		{

			if (commands->next)
			{

				queue_item *item;

				commands = commands->next;
				item = (queue_item*)commands->data;


				if (item->message)
				{
					dbg_cbs->send_message(item->message->str, "grey");
				}

				gdb_input_write_line(item->command->str);

				gdb_id_out = g_io_add_watch(gdb_ch_out, G_IO_IN, on_read_async_output, commands);
			}
			else
			{

				free_commands_queue(commands);


				g_source_remove(gdb_id_out);


				update_files();


				exec_async_command("-exec-run &");
			}
		}
		else
		{
			queue_item *item = (queue_item*)commands->data;
			if(item->error_message)
			{
				if (item->format_error_message)
				{
					gchar* gdb_msg = g_strcompress(strstr(coma, "msg=\"") + strlen("msg=\""));

					GString *msg = g_string_new("");
					g_string_printf(msg, item->error_message->str, gdb_msg);
					dbg_cbs->report_error(msg->str);

					g_free(gdb_msg);
					g_string_free(msg, FALSE);
				}
				else
				{
					dbg_cbs->report_error(item->error_message->str);
				}
			}


			free_commands_queue(commands);

			stop();
		}
	}

	g_free(line);

	return TRUE;
}
