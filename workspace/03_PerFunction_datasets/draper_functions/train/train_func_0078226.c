paste_flush(int send)
{
	if (paste_prompt) {
		gui_entry_set_text(active_entry, paste_entry);
		gui_entry_set_pos(active_entry, paste_entry_pos);
		g_free_and_null(paste_entry);
	}

	if (send)
		paste_send();
	g_array_set_size(paste_buffer, 0);

	gui_entry_set_prompt(active_entry,
			     paste_old_prompt == NULL ? "" : paste_old_prompt);
	g_free(paste_old_prompt); paste_old_prompt = NULL;
	paste_prompt = FALSE;

	paste_line_count = 0;

	gui_entry_redraw(active_entry);
}
