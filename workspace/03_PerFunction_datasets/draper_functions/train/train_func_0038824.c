insert_text_handler (GtkEditable *editable,
                     const gchar *text,
                     gint         length,
                     gint        *position,
                     GladeNamedIconChooserDialog *dialog)
{
	if (is_well_formed (text))
	{

		g_signal_handlers_block_by_func (editable, (gpointer) insert_text_handler, dialog);

		gtk_editable_insert_text (editable, text, length, position);

		g_signal_handlers_unblock_by_func (editable, (gpointer) insert_text_handler, dialog);

	}
	else
	{
		gdk_display_beep (gtk_widget_get_display (GTK_WIDGET (dialog)));
	}

	g_signal_stop_emission_by_name (editable, "insert-text");
}
