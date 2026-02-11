menu_search_prev ()
{
	GtkXText *xtext = GTK_XTEXT (current_sess->gui->xtext);
	xtext_buffer *buf = xtext->buffer;

	if (!gtk_xtext_search(xtext, buf->search_text,
		(buf->search_flags & (case_match | follow | regexp)) | backward, NULL))
	{
		fe_message (_("Search hit end, not found."), FE_MSG_ERROR);
	}
}
