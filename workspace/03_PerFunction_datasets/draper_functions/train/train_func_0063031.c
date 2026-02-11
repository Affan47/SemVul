uint_cell_editing_started (GtkCellRenderer *cell,
                           GtkCellEditable *editable,
                           const gchar     *path,
                           gpointer         user_data)
{
	if (!GTK_IS_ENTRY (editable)) {
		g_warning ("%s: Unexpected cell editable type.", __func__);
		return;
	}


	g_free (last_edited);
	last_edited = NULL;
	g_free (last_path);
	last_path = g_strdup (path);
	last_column = GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (cell), "column"));


	g_signal_connect (G_OBJECT (editable), "insert-text",
	                  (GCallback) uint_filter_cb,
	                  user_data);

	g_signal_connect_after (G_OBJECT (editable), "delete-text",
	                        (GCallback) delete_text_cb,
	                        user_data);


	g_signal_connect (G_OBJECT (editable), "changed",
	                  (GCallback) cell_changed_cb,
	                  cell);


	g_signal_connect (G_OBJECT (editable), "key-press-event",
	                  (GCallback) key_pressed_cb,
	                  user_data);
}
