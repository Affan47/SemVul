undo_redo_real(GtkTextBuffer *buffer)
{
	GtkTextIter start_iter, end_iter;
	UndoInfo *ri;

	if (g_list_length(redo_list)) {

		ri = g_list_last(redo_list)->data;
		gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, ri->start);
		switch (ri->command) {
		case INS:
			gtk_text_buffer_insert(buffer, &start_iter, ri->str, -1);
			break;
		default:
			gtk_text_buffer_get_iter_at_offset(buffer, &end_iter, ri->end);
			gtk_text_buffer_delete(buffer, &start_iter, &end_iter);
		}
		undo_list = g_list_append(undo_list, ri);
		redo_list = g_list_delete_link(redo_list, g_list_last(redo_list));
DV(g_print("cb_edit_redo: undo left = %d, redo left = %d\n",
g_list_length(undo_list), g_list_length(redo_list)));

		if (ri->seq) {
			undo_set_sequency(TRUE);
			return TRUE;
		}
		if (!g_list_length(redo_list))
			gtk_widget_set_sensitive(redo_w, FALSE);
		gtk_widget_set_sensitive(undo_w, TRUE);
		gtk_text_buffer_place_cursor(buffer, &start_iter);
		scroll_to_cursor(buffer, 0.05);
	}
	undo_check_modified_step(buffer);
	return FALSE;
}
