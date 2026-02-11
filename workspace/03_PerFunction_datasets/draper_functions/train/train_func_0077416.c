brasero_jacket_edit_colours_changed_cb (GtkColorButton *button,
					BraseroJacketEdit *self)
{
	BraseroJacketEditPrivate *priv;
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	GdkColor color;
	GtkTextTag *tag;

	priv = BRASERO_JACKET_EDIT_PRIVATE (self);
	if (!priv->current_view)
		return;

	brasero_tool_color_picker_get_color (BRASERO_TOOL_COLOR_PICKER (button), &color);

	buffer = brasero_jacket_view_get_active_buffer (BRASERO_JACKET_VIEW (priv->current_view));
	tag = gtk_text_buffer_create_tag (buffer, NULL,
					  "foreground-gdk", &color,
					  NULL);
	if (!gtk_text_buffer_get_has_selection (buffer)) {
		brasero_jacket_buffer_add_default_tag (BRASERO_JACKET_BUFFER (buffer), tag);
		return;
	}

	gtk_text_buffer_get_selection_bounds (buffer, &start, &end);
	gtk_text_buffer_apply_tag (buffer, tag, &start, &end);
}
