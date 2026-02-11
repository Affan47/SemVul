gtk_source_search_context_replace (GtkSourceSearchContext  *search,
				   const GtkTextIter       *match_start,
				   const GtkTextIter       *match_end,
				   const gchar             *replace,
				   gint                     replace_length,
				   GError                 **error)
{
	GtkTextIter start;
	GtkTextIter end;

	g_return_val_if_fail (GTK_SOURCE_IS_SEARCH_CONTEXT (search), FALSE);
	g_return_val_if_fail (match_start != NULL, FALSE);
	g_return_val_if_fail (match_end != NULL, FALSE);
	g_return_val_if_fail (replace != NULL, FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	if (dispose_has_run (search))
	{
		return FALSE;
	}

	if (!smart_forward_search (search, match_start, &start, &end))
	{
		return FALSE;
	}

	if (!gtk_text_iter_equal (match_start, &start) ||
	    !gtk_text_iter_equal (match_end, &end))
	{
		return FALSE;
	}

	if (gtk_source_search_settings_get_regex_enabled (search->priv->settings))
	{
		return regex_replace (search, &start, &end, replace, error);
	}

	gtk_text_buffer_begin_user_action (search->priv->buffer);
	gtk_text_buffer_delete (search->priv->buffer, &start, &end);
	gtk_text_buffer_insert (search->priv->buffer, &start, replace, replace_length);
	gtk_text_buffer_end_user_action (search->priv->buffer);

	return TRUE;
}
