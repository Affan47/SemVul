brasero_jacket_edit_justify (GtkToggleToolButton *button,
			     BraseroJacketEdit *self,
			     GtkJustification justify)
{
	BraseroJacketEditPrivate *priv;
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	GtkTextTag *tag;

	priv = BRASERO_JACKET_EDIT_PRIVATE (self);

	if (!gtk_toggle_tool_button_get_active (button))
		return;

	if (!priv->current_view)
		return;

	buffer = brasero_jacket_view_get_active_buffer (BRASERO_JACKET_VIEW (priv->current_view));
	tag = gtk_text_buffer_create_tag (buffer, NULL,
					  "justification", justify,
					  NULL);

	if (!gtk_text_buffer_get_has_selection (buffer)) {
		GtkTextMark *mark;

		mark = gtk_text_buffer_get_insert (buffer);
		gtk_text_buffer_get_iter_at_mark (buffer, &start, mark);
		gtk_text_buffer_get_iter_at_mark (buffer, &end, mark);
		brasero_jacket_buffer_add_default_tag (BRASERO_JACKET_BUFFER (buffer), tag);
	}
	else
		gtk_text_buffer_get_selection_bounds (buffer, &start, &end);

	gtk_text_iter_set_line_index (&start, 0);
	gtk_text_iter_forward_to_line_end (&end);
	gtk_text_buffer_apply_tag (buffer, tag, &start, &end);
}
