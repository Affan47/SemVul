e_text_retrieve_surrounding_cb (GtkIMContext *context,
                                EText *text)
{
	gtk_im_context_set_surrounding (
		context, text->text, strlen (text->text),
		g_utf8_offset_to_pointer (text->text, MIN (
		text->selection_start, text->selection_end)) - text->text);

	return TRUE;
}
