insert_text_handler (GtkTextBuffer               *buffer,
                     GtkTextIter                 *pos,
                     const gchar                 *text,
                     gint                         length,
                     GtkSourceUndoManagerDefault *manager)
{
	GtkSourceUndoAction undo_action;
	GtkTextIter selstart;
	GtkTextIter selend;

	if (manager->priv->running_not_undoable_actions > 0)
		return;

	gtk_text_buffer_get_selection_bounds (buffer, &selstart, &selend);

	undo_action.action_type = GTK_SOURCE_UNDO_ACTION_INSERT;

	undo_action.action.insert.pos    = gtk_text_iter_get_offset (pos);
	undo_action.action.insert.text   = (gchar*) text;
	undo_action.action.insert.length = length;
	undo_action.action.insert.chars  = g_utf8_strlen (text, length);

	undo_action.action.insert.selection_start = gtk_text_iter_get_offset (&selstart);
	undo_action.action.insert.selection_end = gtk_text_iter_get_offset (&selend);

	if ((undo_action.action.insert.chars > 1) || (g_utf8_get_char (text) == '\n'))

		undo_action.mergeable = FALSE;
	else
		undo_action.mergeable = TRUE;

	undo_action.modified = FALSE;

	add_action (manager, &undo_action);
}
