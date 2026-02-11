goto_typed (GtkEditable *editable,
                     const gchar *text,
                     gint         length,
                     gint        *position,
                     gpointer user_data)
{
	if (is_valid_digits_only ((gchar *)text))
	{
		g_signal_handlers_block_by_func (editable, (gpointer) goto_typed, user_data);
		gtk_editable_insert_text (editable, text, length, position);
		g_signal_handlers_unblock_by_func (editable, (gpointer) goto_typed, user_data);
		goto_line_activate(GTK_ENTRY(editable), user_data);
		gtk_widget_grab_focus(GTK_WIDGET(editable));
	}
	else
	{
		gdk_display_beep (gtk_widget_get_display (GTK_WIDGET (editable)));
	}

	g_signal_stop_emission_by_name (editable, "insert-text");
}
