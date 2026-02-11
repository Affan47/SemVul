basic_backward_regex_search (GtkSourceSearchContext *search,
			     const GtkTextIter      *start_at,
			     GtkTextIter            *match_start,
			     GtkTextIter            *match_end,
			     const GtkTextIter      *limit)
{
	GtkTextIter start;
	GtkTextIter real_start;
	GtkTextIter end;
	gint start_pos;
	gchar *subject;
	gssize subject_length;
	GRegexMatchFlags match_options;
	GMatchInfo *match_info;
	GtkTextIter iter;
	gint iter_byte_pos;
	gboolean found = FALSE;
	GtkTextIter tmp_match_start;
	GtkTextIter tmp_match_end;

	if (search->priv->regex == NULL ||
	    search->priv->regex_error != NULL)
	{
		return FALSE;
	}

	if (limit == NULL)
	{
		gtk_text_buffer_get_start_iter (search->priv->buffer, &start);
	}
	else
	{
		start = *limit;
	}

	regex_search_get_real_start (search, &start, &real_start, &start_pos);

	end = *start_at;

	match_options = regex_search_get_match_options (&real_start, &end);

	subject = gtk_text_iter_get_visible_text (&real_start, &end);
	subject_length = strlen (subject);

	g_regex_match_full (search->priv->regex,
			    subject,
			    subject_length,
			    start_pos,
			    match_options,
			    &match_info,
			    &search->priv->regex_error);

	iter = real_start;
	iter_byte_pos = 0;

	while (regex_search_fetch_match (match_info,
					 subject,
					 subject_length,
					 &iter,
					 &iter_byte_pos,
					 &tmp_match_start,
					 &tmp_match_end))
	{
		found = TRUE;

		*match_start = tmp_match_start;
		*match_end = tmp_match_end;

		g_match_info_next (match_info, &search->priv->regex_error);
	}

	if (search->priv->regex_error != NULL)
	{
		g_object_notify (G_OBJECT (search), "regex-error");
		found = FALSE;
	}

	g_free (subject);
	g_match_info_free (match_info);

	return found;
}
