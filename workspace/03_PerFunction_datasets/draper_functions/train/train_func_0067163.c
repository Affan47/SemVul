ping_foreach (Netinfo * netinfo, gchar * line, gssize len,
	      gpointer user_data)
{
	gchar *text_utf8;
	gsize bytes_written;
	GtkTextBuffer *buffer = NULL;
	GtkTextIter iter;

	g_return_if_fail (netinfo != NULL);
	g_return_if_fail (line != NULL);

	buffer =
	    gtk_text_view_get_buffer (GTK_TEXT_VIEW (netinfo->output));
	gtk_text_buffer_get_end_iter (buffer, &iter);

	if (len > 0) {
		text_utf8 = g_locale_to_utf8 (line, len,
					      NULL, &bytes_written, NULL);

		gtk_text_buffer_insert
		    (GTK_TEXT_BUFFER (buffer), &iter, text_utf8,
		     bytes_written);
		g_free (text_utf8);
	}
}
