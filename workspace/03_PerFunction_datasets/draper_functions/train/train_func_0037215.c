paste_send(void)
{
	HISTORY_REC *history;
	unichar *arr;
	GString *str;
	char out[10], *text;
	unsigned int i;

	if (paste_join_multiline)
		paste_buffer_join_lines(paste_buffer);

	arr = (unichar *) paste_buffer->data;
	if (active_entry->text_len == 0)
		i = 0;
	else {


		for (i = 0; i < paste_buffer->len; i++) {
			if (arr[i] == '\r' || arr[i] == '\n') {
				i++;
				break;
			}

			gui_entry_insert_char(active_entry, arr[i]);
		}

		text = gui_entry_get_text(active_entry);
		history = command_history_current(active_win);
		command_history_add(history, text);

		signal_emit("send command", 3, text,
			    active_win->active_server, active_win->active);
		g_free(text);
	}


	str = g_string_new(NULL);
	for (; i < paste_buffer->len; i++) {
		if (arr[i] == '\r' || arr[i] == '\n') {
			history = command_history_current(active_win);
			command_history_add(history, str->str);

			signal_emit("send command", 3, str->str,
				    active_win->active_server,
				    active_win->active);
			g_string_truncate(str, 0);
		} else if (active_entry->utf8) {
			out[g_unichar_to_utf8(arr[i], out)] = '\0';
			g_string_append(str, out);
		} else if (term_type == TERM_TYPE_BIG5) {
			if (arr[i] > 0xff)
				g_string_append_c(str, (arr[i] >> 8) & 0xff);
			g_string_append_c(str, arr[i] & 0xff);
		} else {
			g_string_append_c(str, arr[i]);
		}
	}

	gui_entry_set_text(active_entry, str->str);
	g_string_free(str, TRUE);
}
