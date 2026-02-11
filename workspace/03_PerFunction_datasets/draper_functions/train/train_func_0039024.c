line_has_prefix (GitgDiffView *view, guint line, gchar const *prefix)
{
	GtkTextIter iter;

	gtk_text_buffer_get_iter_at_line (view->priv->current_buffer, &iter, line);

	GtkTextIter end = iter;

	if (!gtk_text_iter_forward_chars (&end, g_utf8_strlen (prefix, -1)))
	{
		return FALSE;
	}

	gchar *text = gtk_text_iter_get_text (&iter, &end);
	gboolean ret = g_str_has_prefix (text, prefix);
	g_free (text);

	return ret;
}
