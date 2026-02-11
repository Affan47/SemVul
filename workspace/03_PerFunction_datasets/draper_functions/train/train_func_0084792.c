undo_insert_text_cb(GtkTextBuffer *textbuf, GtkTextIter *iter,
			 gchar *new_text, gint new_text_length,
			 UndoMain *undostruct)
{
	gchar *text_to_insert;
	gint pos;
	if (prefs_common.undolevels <= 0) return;

	pos = gtk_text_iter_get_offset(iter);
	if (undostruct->wrap && undostruct->undo) {
		UndoInfo *last_undo = undostruct->undo->data;
		if (last_undo && (last_undo->action == UNDO_ACTION_INSERT
				  || last_undo->action == UNDO_ACTION_REPLACE_INSERT)
		&&  last_undo->start_pos < pos && last_undo->end_pos > pos) {
			GtkTextIter start,end;
			last_undo->end_pos += g_utf8_strlen(new_text, -1);
			gtk_text_buffer_get_iter_at_offset(textbuf, &start, last_undo->start_pos);
			gtk_text_buffer_get_iter_at_offset(textbuf, &end, last_undo->end_pos);
			g_free(last_undo->text);
			last_undo->text = gtk_text_buffer_get_text(textbuf, &start, &end, FALSE);
			debug_print("add:undo upd %d-%d\n", last_undo->start_pos, last_undo->end_pos);
			return;
		} else if (last_undo)
			debug_print("add:last: %d, %d-%d (%d)\n", last_undo->action,
				last_undo->start_pos, last_undo->end_pos, pos);
	}
	Xstrndup_a(text_to_insert, new_text, new_text_length, return);
	debug_print("add:undo add %d-%ld\n", pos, pos + g_utf8_strlen(text_to_insert, -1));
	undo_add(text_to_insert, pos, pos + g_utf8_strlen(text_to_insert, -1),
		 UNDO_ACTION_INSERT, undostruct);
}
